/* 
 * Copyright (C) 2021 AZZ (aka) BLACKBURN
 *
 * File:    IODriver.hpp
 * Author:  Ahmed Ziabat Ziabat
 * Created: 2021-11-19
 */

#include <types.h>
#include <System/Driver.hpp>

#ifndef IODRIVER_H
#define IODRIVER_H

namespace InputOutputDriver{
	struct driverData{
		unsigned int size;
		void * data;
	};

	typedef struct driverData DriverData;

	class IODriver: public Driver
	{
		private:
			uint32_t uptime;
		protected:
			void updateUptime(uint32_t &uptime);
		public:
			virtual int write(DriverData * driverData);
			virtual DriverData * read();
			virtual DriverData * read(unsigned int size);
	};
}

#endif