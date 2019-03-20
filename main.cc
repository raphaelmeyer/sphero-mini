#include <dbus/dbus-glib.h>

#include <cassert>

int main() {
  GError *error = nullptr;
  auto conn = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
  assert(not error);
  assert(conn);

  auto proxy = dbus_g_proxy_new_for_name_owner(
    conn,
    "org.bluez",
    "/org/bluez/hci0/dev_B0_B4_48_BD_D0_83",
    "org.bluez.Device1",
    &error
  );
  assert(proxy);
  assert(not error);

  return 0;
}

