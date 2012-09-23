#ifndef DISCHARGER_H
#define DISCHARGER_H

#include "AnalogInputs.h"
#include "Timer.h"

#define DISCHARGER_UPPERBOUND_VALUE ((F_CPU / 2000000) * INTERRUPT_PERIOD_MICROSECONDS)
#define DISCHARGER_TEMPERATURE_DISABLE ANALOG_CELCIUS(60)
#define DISCHARGER_TEMPERATURE_ENABLE  ANALOG_CELCIUS(55)

class Discharger {
public:
	enum STATE { DISCHARGING, DISCHARGING_COMPLETE, ERROR};
	static const AnalogInputs::Name VName = AnalogInputs::VoutBalancer;
	static const AnalogInputs::Name IName = AnalogInputs::Idischarge;

	Discharger();

	static AnalogInputs::ValueType getVout();
	static AnalogInputs::ValueType getIout();

	STATE getState() const { return state_; }
	bool isPowerOn() const { return getState() == DISCHARGING; }

	uint16_t getValue() const { return value_; }
	void setValue(uint16_t value);
	void setRealValue(uint16_t I);

	void powerOn();
	void powerOff(STATE reason = DISCHARGING_COMPLETE);

	void doInterrupt();

	uint32_t getOnTimeSec() const;
	double getDischarge() const;

	uint16_t correctValueTintern(uint16_t v);

protected:
	void finalizeValueTintern(bool force);
	STATE state_;
	uint16_t value_,valueSet_;
	uint16_t startTime_;
	bool tempcutoff_;
	double discharge_;
};


#endif //DISCHARGER_H