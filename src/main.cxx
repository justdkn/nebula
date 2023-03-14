#include <iostream>
#include <orm/orm.hxx>
#include "db.hxx"
#include "file_manager.hxx"

int main() {
  Driver& driver = get_db();
  std::cout << "连接数据库: "
            << driver.connect("127.0.0.1", 3306, "root", "123456", "nebula")
            << std::endl;
  driver.transaction();
  try {
    auto file = file_manager::create_folder(std::nullopt, "下载");
    if (file) {
      std::cout << "创建文件夹\"下载\"成功" << std::endl;
      auto child_file = file_manager::create_folder(file->uuid, "图片");
      if (child_file) {
        std::cout << "创建文件夹\"下载\\图片\"成功" << std::endl;
      } else {
        std::cout << "创建文件夹\"下载\\图片\"失败" << std::endl;
      }
    } else {
      std::cout << "创建文件夹\"下载\"失败" << std::endl;
    }
    driver.commit();
  } catch (std::exception& e) {
    driver.rollback();
    std::cout << "创建文件夹异常: " << e.what() << std::endl;
  }

  std::cout << "\"\\\" 目录列表" << std::endl;
  auto files = file_manager::folder_list(std::nullopt);
  for (auto& file : files) {
    std::cout << file << std::endl;
  }

  if (files.size() > 0) {
    std::cout << "\"\\" << files[0].name << "\" 目录列表" << std::endl;
    auto download_files = file_manager::folder_list(files[0].uuid);
    for (auto& file : download_files) {
      std::cout << file << std::endl;
    }
  }

  std::cout << "断开数据库" << std::endl;
  driver.disconnect();
  return 0;
}