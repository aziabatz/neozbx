/* 
 * Copyright (C) 2021 AZZ (aka) BLACKBURN
 *
 * File:    IODriver.hpp
 * Author:  Ahmed Ziabat Ziabat
 * Created: 2021-11-19
 */

namespace InputOutputDriver{
	class IODriver: public Driver
	{
		private:
			uint32_t uptime;
		protected:
			void updateUptime(uint32_t &uptime);
		public:
			int write(DriverData * data);
			DriverData * read();
	};
}
