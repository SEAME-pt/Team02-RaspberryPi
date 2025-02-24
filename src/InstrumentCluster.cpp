#include "InstrumentCluster.hpp"

InstrumentCluster::InstrumentCluster(QObject* parent)
    : QObject(parent),
      m_session(Session::open(std::move(Config::create_default()))),
      m_subSpeed(m_session.declare_subscriber(
          "seame/car/1/speedSensor",
          [this](const Sample& sample)
          {
              int speed = std::stoi(sample.get_payload().as_string());
              std::cout << "Sub speed" << std::endl;
              this->setSpeed(speed);
          },
          closures::none)),
      m_subBattery(m_session.declare_subscriber(
          "seame/car/1/batterySensor",
          [this](const Sample& sample)
          {
              int batteryPercentage =
                  std::stoi(sample.get_payload().as_string());
              BatteryStatus battery;
              battery.percentage = batteryPercentage;
              std::cout << "Sub battery" << std::endl;
              this->setBattery(battery);
          },
          closures::none)),
      m_subLights(m_session.declare_subscriber(
          "seame/car/1/lights",
          [this](const Sample& sample)
          {
              uint8_t data =
                  static_cast<uint8_t>(sample.get_payload().as_string()[0]);

              LightStatus lights;
              lights.rightBlinker  = (data & (1 << 0)) != 0;
              lights.leftBlinker   = (data & (1 << 1)) != 0;
              lights.lowBeam       = (data & (1 << 2)) != 0;
              lights.highBeam      = (data & (1 << 3)) != 0;
              lights.frontFogLight = (data & (1 << 4)) != 0;
              lights.rearFogLight  = (data & (1 << 5)) != 0;
              lights.hazardLight   = (data & (1 << 6)) != 0;
              lights.parkingLight  = (data & (1 << 7)) != 0;
              std::cout << "Sub lights" << std::endl;
              this->setLights(lights);
          },
          closures::none)),
      m_subGear(m_session.declare_subscriber(
          "seame/car/1/gear",
          [this](const Sample& sample)
          {
              uint8_t data =
                  static_cast<uint8_t>(sample.get_payload().as_string()[0]);

              GearPosition gear;
              gear.park    = (data & (1 << 0)) != 0;
              gear.reverse = (data & (1 << 1)) != 0;
              gear.neutral = (data & (1 << 2)) != 0;
              gear.drive   = (data & (1 << 3)) != 0;
              std::cout << "Sub gear" << std::endl;
              this->setGear(gear);
          },
          closures::none)),
      m_speed(0)
{
}

InstrumentCluster::InstrumentCluster(const std::string& configFile,
                                     QObject* parent)
    : QObject(parent),
      m_session(Session::open(std::move(Config::from_file(configFile)))),
      m_subSpeed(m_session.declare_subscriber(
          "seame/car/1/speedSensor",
          [this](const Sample& sample)
          {
              int speed = std::stoi(sample.get_payload().as_string());
              std::cout << "Sub speed" << std::endl;
              this->setSpeed(speed);
          },
          closures::none)),
      m_subBattery(m_session.declare_subscriber(
          "seame/car/1/batterySensor",
          [this](const Sample& sample)
          {
              int batteryPercentage =
                  std::stoi(sample.get_payload().as_string());
              BatteryStatus battery;
              battery.percentage = batteryPercentage;
              std::cout << "Sub battery" << std::endl;
              this->setBattery(battery);
          },
          closures::none)),
      m_subLights(m_session.declare_subscriber(
          "seame/car/1/lights",
          [this](const Sample& sample)
          {
              uint8_t data =
                  static_cast<uint8_t>(sample.get_payload().as_string()[0]);

              LightStatus lights;
              lights.rightBlinker  = (data & (1 << 0)) != 0;
              lights.leftBlinker   = (data & (1 << 1)) != 0;
              lights.lowBeam       = (data & (1 << 2)) != 0;
              lights.highBeam      = (data & (1 << 3)) != 0;
              lights.frontFogLight = (data & (1 << 4)) != 0;
              lights.rearFogLight  = (data & (1 << 5)) != 0;
              lights.hazardLight   = (data & (1 << 6)) != 0;
              lights.parkingLight  = (data & (1 << 7)) != 0;
              std::cout << "Sub lights" << std::endl;
              this->setLights(lights);
          },
          closures::none)),
      m_subGear(m_session.declare_subscriber(
          "seame/car/1/gear",
          [this](const Sample& sample)
          {
              uint8_t data =
                  static_cast<uint8_t>(sample.get_payload().as_string()[0]);

              GearPosition gear;
              gear.park    = (data & (1 << 0)) != 0;
              gear.reverse = (data & (1 << 1)) != 0;
              gear.neutral = (data & (1 << 2)) != 0;
              gear.drive   = (data & (1 << 3)) != 0;
              std::cout << "Sub gear" << std::endl;
              this->setGear(gear);
          },
          closures::none)),
      m_speed(0)
{
}

InstrumentCluster::~InstrumentCluster()
{
    m_session.close();
}

int InstrumentCluster::getSpeed() const
{
    return m_speed;
}

BatteryStatus InstrumentCluster::getBattery() const
{
    return m_battery;
}

LightStatus InstrumentCluster::getLights() const
{
    return m_lights;
}

GearPosition InstrumentCluster::getGear() const
{
    return m_gear;
}

void InstrumentCluster::setSpeed(int speed)
{
    if (m_speed != speed)
    {
        m_speed = speed;
        emit speedChanged(m_speed);
    }
}

void InstrumentCluster::setBattery(BatteryStatus battery)
{
    if (m_battery != battery)
    {
        m_battery = battery;
        emit batteryChanged(m_battery);
    }
}

void InstrumentCluster::setLights(LightStatus lights)
{
    if (m_lights != lights)
    {
        m_lights = lights;
        emit lightsChanged(m_lights);
    }
}

void InstrumentCluster::setGear(GearPosition gear)
{
    if (m_gear != gear)
    {
        m_gear = gear;
        emit gearChanged(m_gear);
    }
}
