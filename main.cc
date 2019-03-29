#include <dbus/dbus.h>

#include <iostream>
#include <stdexcept>

int main() {

  DBusError dbus_error;
  const char * dbus_result = nullptr;

  ::dbus_error_init(&dbus_error);

  auto dbus_conn = ::dbus_bus_get(DBUS_BUS_SYSTEM, &dbus_error);
  if(not dbus_conn) {
    throw std::runtime_error{dbus_error.message};
  }

  auto dbus_msg =
    ::dbus_message_new_method_call("org.bluez", "/org/bluez/hci0/dev_FF_57_53_15_5E_4E", "org.freedesktop.DBus.Introspectable", "Introspect");
  if(not dbus_msg) {
    ::dbus_connection_unref(dbus_conn);
    throw std::runtime_error{dbus_error.message};
  }

  auto dbus_reply =
    ::dbus_connection_send_with_reply_and_block(dbus_conn, dbus_msg, DBUS_TIMEOUT_USE_DEFAULT, &dbus_error);
  if(not dbus_reply) {
    ::dbus_message_unref(dbus_msg);
    ::dbus_connection_unref(dbus_conn);
    throw std::runtime_error{dbus_error.message};
  }

  if(not::dbus_message_get_args(dbus_reply, &dbus_error, DBUS_TYPE_STRING, &dbus_result, DBUS_TYPE_INVALID)) {
    ::dbus_message_unref(dbus_reply);
    ::dbus_message_unref(dbus_msg);
    ::dbus_connection_unref(dbus_conn);
    throw std::runtime_error{dbus_error.message};
  }

  std::cout << "Connected to D-Bus as \"" << ::dbus_bus_get_unique_name(dbus_conn) << "\"." << std::endl;
  std::cout << "Introspection Result:" << std::endl << std::endl;
  std::cout << dbus_result << std::endl;
  ::dbus_message_unref(dbus_msg);
  ::dbus_message_unref(dbus_reply);

  ::dbus_connection_unref(dbus_conn);

  /*
      "org.bluez",
      "/org/bluez/hci0/dev_FF_57_53_15_5E_4E",
      "org.bluez.Device1",
  */

  return 0;
}
