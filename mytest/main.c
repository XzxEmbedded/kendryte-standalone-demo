/* Copyright 2018 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <bsp.h>
#include <sysctl.h>
#include <otp.h>
#include "uart.h"

uint8_t otp_read[16*1024];
uint8_t chipid[OTP_SYSTEM_BLOCK_SIZE];
uint8_t aes_key[16] = {0};

int main(void)
{
	otp_status_t status;

	//sysctl_pll_set_freq(SYSCTL_PLL0, 320000000);
	sysctl_clock_set_clock_select(SYSCTL_CLOCK_SELECT_ACLK, SYSCTL_SOURCE_IN0);
	uart_debug_init(-1);

	uint64_t core = current_coreid();

	otp_init(0);
	printf("Core %ld Hello world\n", core);

	status = otp_read_byte(0x0, otp_read, 0x3FF0);
	printf("otp_read_byte status = %d \n", status);
	for(int i = 0; i< 0x3FF0; i++) {
		if(i == 0x0)
			printf("COMMON_DATA[0x0~0x3ACF] \n");
		if(i == 0x3AD0)
			printf("SYSTEM_DATA[0x3AD0~0x3DCF] \n");
		if(i == 0x3DD0)
			printf("OTP_BISR_DATA_ADDR[0x3DD0~0x3FCF] \n");
		if(i == 0x3FD0)
			printf("OTP_BLOCK_CTL_ADDR[0x3FD0~0x3FDF] \n");
		if(i == 0x3FE0)
			printf("OTP_WIRED_REG_ADDR[0x3FE0~0x3FEF] \n");
		if(i % 16 == 0)
			printf("[0x%04x]", i);
		printf("%02x ", otp_read[i]);
		if(i % 16 == 15)
			printf("\n");
	}

	status = otp_key_compare(aes_key);
	if(OTP_OK == status)
		printf("OTP_AES_KEY_ADDR[0x3FF0~0x3FFF]\n[0x3ef0]16*00");
	else
		printf("aes key fail\n");
	printf("\n");

	while(1)
		;

	return 0;
}
