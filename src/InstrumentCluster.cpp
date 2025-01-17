#include "../include/InstrumentCluster.hpp"

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
              int battery = std::stoi(sample.get_payload().as_string());
              std::cout << "Sub battery" << std::endl;
              this->setBattery(battery);
          },
          closures::none)),
      m_subLights(m_session.declare_subscriber(
          "seame/car/1/lights",
          [this](const Sample& sample)
          {
              LightStatus lights;
              memcpy(&lights, sample.get_payload().as_string().c_str(),
                     sizeof(LightStatus));
              std::cout << "Sub lights" << std::endl;
              this->setLights(lights);
          },
          closures::none)),
      m_subGear(m_session.declare_subscriber(
          "seame/car/1/gear",
          [this](const Sample& sample)
          {
              GearPosition gear;
              memcpy(&gear, sample.get_payload().as_string().c_str(),
                     sizeof(GearPosition));
              std::cout << "Sub gear" << std::endl;
              this->setGear(gear);
          },
          closures::none)),
      m_speed(0), m_battery(0), m_gear(GearPosition::PARK)
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

int InstrumentCluster::getBattery() const
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

void InstrumentCluster::setBattery(int battery)
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
