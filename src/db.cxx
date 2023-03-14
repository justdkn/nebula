#include "db.hxx"

Driver driver_g;

Driver& get_db() {
  return driver_g;
}