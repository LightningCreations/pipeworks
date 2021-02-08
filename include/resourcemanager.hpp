#ifndef PW_RESOURCEMANAGER_HPP
#define PW_RESOURCEMANAGER_HPP

#include <atomic>
#include <map>
#include <shared_mutex>
#include <string>

#include "imagedata.hpp"

namespace pipeworks {

class ResourceManager {
  private:
    std::map<std::string, ImageData*> loaded_imagedata;
    std::shared_mutex access_mutex;
  public:
    ResourceManager();
    ImageData &get_image_data(const std::string &name);
    bool is_image_data_loaded(const std::string &name);
    void put_image_data(const std::string &name, ImageData *imagedata);
};

extern ResourceManager g_resourcemanager;

}

#endif // PW_RESOURCEMANAGER_HPP
