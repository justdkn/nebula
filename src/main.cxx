#include <iostream>
#include <orm/orm.hxx>
#include "common/db.hxx"
#include "logic/file_logic.hxx"
#include <dotenv.hxx>

int main() {
  dotenv::config();
  Driver& driver = get_db();
  std::cout << "连接数据库: "
            << driver.connect("127.0.0.1", 3306, "root", "123456", "nebula")
            << std::endl;

  driver.transaction();
  try {
    auto file = file_logic::create_folder(std::nullopt, "下载");
    if (file) {
      std::cout << "创建文件夹\"下载\"成功" << std::endl;
      auto child_file = file_logic::create_folder(file->uuid, "图片");
      if (child_file) {
        std::cout << "创建文件夹\"下载\\图片\"成功" << std::endl;
        auto img_file = file_logic::create_file(child_file->uuid, "1.bmp");
        if (img_file) {
          std::cout << "创建文件\"下载\\图片\\1.bmp\"成功" << std::endl;
        } else {
          std::cout << "创建文件\"下载\\图片\\1.bmp\"失败" << std::endl;
        }
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

  driver.transaction();
  try {
    auto file = file_logic::get(std::nullopt, "下载");
    file      = file_logic::get(file->uuid, "图片");
    if (file && file_logic::move(file->uuid.value(), std::nullopt, "测试")) {
      std::cout << "移动文件夹\"下载\\图片\" => \"测试\" 成功" << std::endl;
    } else {
      std::cout << "移动文件夹\"下载\\图片\" => \"测试\" 失败" << std::endl;
    }
    driver.commit();
  } catch (std::exception& e) {
    driver.rollback();
    std::cout << "移动文件夹异常: " << e.what() << std::endl;
  }

  driver.transaction();
  try {
    auto file = file_logic::get(std::nullopt, "下载");
    if (file_logic::move(file->uuid, file->parent_uuid, "下载_bak")) {
      std::cout << "重命名文件 \"下载\" => \"下载_bak\" 成功" << std::endl;
    } else {
      std::cout << "重命名文件 \"下载\" => \"下载_bak\" 失败" << std::endl;
    }
    driver.commit();
  } catch (std::exception& e) {
    driver.rollback();
    std::cout << "重命名文件异常: " << e.what() << std::endl;
  }

  // driver.transaction();
  // try {
  //   if (file_logic::remove(std::nullopt, "下载_bak")) {
  //     std::cout << "删除文件 \"下载_bak\" 成功" << std::endl;
  //   } else {
  //     std::cout << "删除文件 \"下载_bak\" 失败" << std::endl;
  //   }
  //   driver.commit();
  // } catch (std::exception& e) {
  //   driver.rollback();
  //   std::cout << "删除文件文件异常: " << e.what() << std::endl;
  // }

  // driver.transaction();
  // try {
  //   auto file = file_logic::get(std::nullopt, "下载_bak");
  //   if (file_logic::remove(file->uuid, "图片")) {
  //     std::cout << "删除文件 \"下载_bak\\图片\" 成功" << std::endl;
  //   } else {
  //     std::cout << "删除文件 \"下载_bak\\图片\" 失败" << std::endl;
  //   }
  //   driver.commit();
  // } catch (std::exception& e) {
  //   driver.rollback();
  //   std::cout << "删除文件文件异常: " << e.what() << std::endl;
  // }

  driver.transaction();
  try {
    if (file_logic::remove(std::nullopt, "下载_bak")) {
      std::cout << "删除文件 \"下载_bak\" 成功" << std::endl;
    } else {
      std::cout << "删除文件 \"下载_bak\" 失败" << std::endl;
    }
    driver.commit();
  } catch (std::exception& e) {
    driver.rollback();
    std::cout << "删除文件文件异常: " << e.what() << std::endl;
  }

  std::cout << "\"\\\" 目录列表" << std::endl;
  auto files = file_logic::list(std::nullopt);
  for (auto& file : files) {
    std::cout << file << std::endl;
    if (file.type && file.type.value() == File::Type::File) {
      std::cout << "path: " << file.path() << std::endl;
    }
  }

  if (files.size() > 0) {
    std::cout << "\"\\" << files[0].name << "\" 目录列表" << std::endl;
    auto download_files = file_logic::list(files[0].uuid);
    for (auto& file : download_files) {
      std::cout << file << std::endl;
      if (file.type && file.type.value() == File::Type::File) {
        std::cout << "path: " << file.path() << std::endl;
      }
    }
  }

  std::cout << "断开数据库" << std::endl;
  driver.disconnect();
  return 0;
}