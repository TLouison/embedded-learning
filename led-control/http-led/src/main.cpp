#include "gpio_pin.h"

#include <httplib.h>
#include <pigpio.h>
#include <nlohmann/json.hpp>
#include <unistd.h>
#include <format>
#include <memory>

using json = nlohmann::json;

#define LED_GPIO_PIN 12

json get_generic_success()
{
    return {{"success", true}};
}

json get_level_response(GpioPin *led)
{
    return {{"level", led->get_level()}, {"success", true}};
}

int main(int argc, char *argv[])
{
    if (gpioInitialise() < 0)
        return 1;

    // Set up GPIO Pin
    std::unique_ptr<GpioPin> led = std::make_unique<GpioPin>(LED_GPIO_PIN, PI_OUTPUT);

    // Set up HTTP server (not HTTPS)
    httplib::Server svr;

    svr.Get("/led/status", [&led](const httplib::Request &, httplib::Response &res)
            { res.set_content(get_level_response(led.get()).dump(), "application/json"); });
    svr.Post("/led/on", [&led](const httplib::Request &, httplib::Response &res)
             { 
            led->set_high();
            res.set_content(get_generic_success().dump(), "application/json"); });
    svr.Post("/led/off", [&led](const httplib::Request &, httplib::Response &res)
             { 
            led->set_low();
            res.set_content(get_generic_success().dump(), "application/json"); });

    svr.listen("0.0.0.0", 8080);

    gpioTerminate();
    return 0;
}
