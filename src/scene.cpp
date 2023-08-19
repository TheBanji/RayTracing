////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <pthread.h>
#include <cmath>
#include "scene.hpp"
#include "random.hpp"
#include "utils.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Scene::Scene(const Point& origin, const Point& screenCenter, const Vector& screenWidth, const Vector& screenHeight) : Camera(origin, screenCenter, screenWidth, screenHeight), _skybox() {}

Scene::Scene(const Scene& scene) : Camera(scene._origin, scene._screenCenter, scene._screenWidth, scene._screenHeight), _skybox(scene._skybox) {
    int i;

    for(i = 0; i < (int)scene._objects.size(); i++) {
        _objects.push_back(scene._objects[i]->clone());
    }

    for(i = 0; i < (int)scene._lights.size(); i++) {
        _lights.push_back(new Light(*(scene._lights[i])));
    }
}

Scene::~Scene() {
    deleteObjects();
    deleteLights();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NB_THREADS 16 // Splitting the rendering onto NB_THREADS - threads.

typedef struct {
    const Scene* scene;
    PPM* image;
    int xStart;
    int xEnd;
    int yStart;
    int yEnd;
    int nbSamplesAliasing;
    int recursionLimit;
} threadData_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::render(PPM& image, int nbSamplesAliasing, int recursionLimit) const {
    int i;
    int widthImage    = image.getWidth(), heightImage = image.getHeight();
    int rootNbThreads = (int)std::sqrt(NB_THREADS);
    threadData_t threadData[NB_THREADS];
    pthread_t threads[NB_THREADS];
    for(i = 0; i < NB_THREADS; i++) { // Splitting the rendering onto NB_THREADS - threads.
        threadData[i].scene             = this;
        threadData[i].image             = &image;
        threadData[i].xStart            = (i%rootNbThreads)*widthImage/rootNbThreads;
        threadData[i].xEnd              = (1+i%rootNbThreads)*widthImage/rootNbThreads;
        threadData[i].yStart            = (i/rootNbThreads)*heightImage/rootNbThreads;
        threadData[i].yEnd              = (1+i/rootNbThreads)*heightImage/rootNbThreads;
        threadData[i].nbSamplesAliasing = nbSamplesAliasing;
        threadData[i].recursionLimit    = recursionLimit;   
        pthread_create(&threads[i], nullptr, &render_chunk, &threadData[i]); // Calling the threads.
    }
    for(i = 0; i < NB_THREADS; i++) { // Joining the threads.
        pthread_join(threads[i], nullptr);
    }
}

void * render_chunk(void * args) {
    threadData_t* data = (threadData_t*)args;
    int i, j, s;
    Ray ray;
    int widthImage = data->image->getWidth(), heightImage = data->image->getHeight();
    for(j = data->yStart; j < data->yEnd; j++) {
        for(i = data->xStart; i < data->xEnd; i++) {
            for(s = 0; s < data->nbSamplesAliasing; s++) {
                ray = Ray(data->scene->_origin, data->scene->_bottom_left_corner + data->scene->_screenWidth*((double)(i+uniform_random())/widthImage)+data->scene->_screenHeight*((double)(j+uniform_random())/heightImage) - data->scene->_origin);
                (*data->image)[heightImage-1-j][i] += data->scene->Scene::cast_ray(ray, data->recursionLimit);
            }
            DEBUG(fprintf(stdout, "Pixel (before) %lf %lf %lf\n", (*data->image)[heightImage-1-j][i].getR(), (*data->image)[heightImage1-j][i].getG(), (*data->image)data->[yEnd-1-j][i].getB());)
            (*data->image)[heightImage-1-j][i] /= data->nbSamplesAliasing;
            DEBUG(fprintf(stdout, "Pixel (after) %lf %lf %lf\n", (*data->image)[heightImage-1-j][i].getR(), (*data->image)[heightImage-1-j][i].getG(), (*data->image)[heightImage-1-j][i].getB());)
        }
    }
    return nullptr;
}

Color Scene::cast_ray(const Ray& shotRay, int recursionLimit) const {
    double minHitTime = MAX_DOUBLE;
    double tmpHitTime;
    Object * hitObject = nullptr;
    for(const auto& obj : _objects) {
        tmpHitTime = obj->intersect(shotRay);
        if(tmpHitTime >= 0.0 && tmpHitTime < minHitTime) {
            hitObject  = obj;
            minHitTime = tmpHitTime; 
        }
    }
    if(minHitTime != MAX_DOUBLE) {
        Ray scatteredRay;
        Color hitObjColor = hitObject->getColor(shotRay, shotRay(minHitTime), scatteredRay);
        DEBUG(fprintf(stdout, "\t\thitObj(%p) %lf %lf %lf\n", (void*)hitObject, hitObjColor.getR(), hitObjColor.getG(), hitObjColor.getB());)
        if(recursionLimit > 0) {
            return hitObjColor * Scene::cast_ray(scatteredRay, recursionLimit-1);
        }
        return hitObjColor;
    }
    double t = shotRay.getDir().getX();
    DEBUG(fprintf(stdout, "\t\tSkybox %lf %lf %lf\n", _skybox(t).getR(), _skybox(t).getG(), _skybox(t).getB());)
    return _skybox(t);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::addObject(Object * object) {
    _objects.push_back(object);
}

void Scene::popObject() {
    Object * tmp;
    if(_objects.size() > 0) {
        tmp = _objects.back();
        _objects.pop_back();
        delete tmp;
    }
}

void Scene::deleteObjects() {
    Object * tmp;
    while(_objects.size() > 0) {
        tmp = _objects.back();
        _objects.pop_back();
        delete tmp;
    }
}

void Scene::addLight(Light * light) {
    _lights.push_back(light);
}

void Scene::popLight() {
    Light * tmp;
    if(_objects.size() > 0) {
        tmp = _lights.back();
        _lights.pop_back();
        delete tmp;
    }
}

void Scene::deleteLights() {
    Light * tmp;
    while(_lights.size() > 0) {
        tmp = _lights.back();
        _lights.pop_back();
        delete tmp;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////