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
  // try {
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
  // } catch (std::exception& e) {
  //   driver.rollback();
  //   std::cout << "异常: " << e.what() << std::endl;
  //   throw e;
  // }

  std::cout << "断开数据库" << std::endl;
  driver.disconnect();
  return 0;
}