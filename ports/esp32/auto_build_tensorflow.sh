file_index=0
for file in `find ../../modules/tensorflow -name "*.cpp"`
do
	echo $file
	objfile=${file/".cpp"/".o"}

	outputfile=${objfile/"../../modules/tensorflow"/"build-GENERIC/tensorflow"}

	# make folders
	mkdir -p ${outputfile%/*}

	xtensa-esp32-elf-g++ -std=gnu++11 -Os -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -mlongcalls -nostdlib -Wall -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=deprecated-declarations -DESP_PLATFORM -I../../lib/berkeley-db-1.xx/PORT/include -I. -I../.. -I../../lib/mp-readline -I../../lib/netutils -I../../lib/timeutils -Ibuild-GENERIC -I/mnt/c/dev/esp-idf/components/bootloader_support/include -I/mnt/c/dev/esp-idf/components/bootloader_support/include_bootloader -I/mnt/c/dev/esp-idf/components/console -I/mnt/c/dev/esp-idf/components/driver/include -I/mnt/c/dev/esp-idf/components/driver/include/driver -I/mnt/c/dev/esp-idf/components/efuse/include -I/mnt/c/dev/esp-idf/components/efuse/esp32/include -I/mnt/c/dev/esp-idf/components/esp32/include -I/mnt/c/dev/esp-idf/components/espcoredump/include -I/mnt/c/dev/esp-idf/components/soc/include -I/mnt/c/dev/esp-idf/components/soc/esp32/include -I/mnt/c/dev/esp-idf/components/heap/include -I/mnt/c/dev/esp-idf/components/log/include -I/mnt/c/dev/esp-idf/components/nvs_flash/include -I/mnt/c/dev/esp-idf/components/freertos/include -I/mnt/c/dev/esp-idf/components/esp_ringbuf/include -I/mnt/c/dev/esp-idf/components/esp_event/include -I/mnt/c/dev/esp-idf/components/tcpip_adapter/include -I/mnt/c/dev/esp-idf/components/lwip/lwip/src/include -I/mnt/c/dev/esp-idf/components/lwip/port/esp32/include -I/mnt/c/dev/esp-idf/components/lwip/include/apps -I/mnt/c/dev/esp-idf/components/lwip/include/apps/sntp -I/mnt/c/dev/esp-idf/components/mbedtls/mbedtls/include -I/mnt/c/dev/esp-idf/components/mbedtls/port/include -I/mnt/c/dev/esp-idf/components/mdns/include -I/mnt/c/dev/esp-idf/components/mdns/private_include -I/mnt/c/dev/esp-idf/components/spi_flash/include -I/mnt/c/dev/esp-idf/components/ulp/include -I/mnt/c/dev/esp-idf/components/vfs/include -I/mnt/c/dev/esp-idf/components/xtensa-debug-module/include -I/mnt/c/dev/esp-idf/components/wpa_supplicant/include -I/mnt/c/dev/esp-idf/components/wpa_supplicant/port/include -I/mnt/c/dev/esp-idf/components/app_trace/include -I/mnt/c/dev/esp-idf/components/app_update/include -I/mnt/c/dev/esp-idf/components/pthread/include -I/mnt/c/dev/esp-idf/components/smartconfig_ack/include -I/mnt/c/dev/esp-idf/components/sdmmc/include -I/mnt/c/dev/esp-idf/components/esp_common/include -I/mnt/c/dev/esp-idf/components/esp_eth/include -I/mnt/c/dev/esp-idf/components/esp_event/private_include -I/mnt/c/dev/esp-idf/components/esp_rom/include -I/mnt/c/dev/esp-idf/components/esp_wifi/include -I/mnt/c/dev/esp-idf/components/esp_wifi/esp32/include -I/mnt/c/dev/esp-idf/components/lwip/include/apps/sntp -I/mnt/c/dev/esp-idf/components/spi_flash/private_include -I/mnt/c/dev/esp-idf/components/wpa_supplicant/include/esp_supplicant -I/mnt/c/dev/esp-idf/components/xtensa/include -I/mnt/c/dev/esp-idf/components/xtensa/esp32/include -I/mnt/c/dev/esp-idf/components/bt/include -I/mnt/c/dev/esp-idf/components/bt/common/osi/include -I/mnt/c/dev/esp-idf/components/bt/common/btc/include -I/mnt/c/dev/esp-idf/components/bt/common/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/porting/nimble/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/port/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/nimble/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/nimble/host/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/nimble/host/services/ans/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/nimble/host/services/bas/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/nimble/host/services/gap/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/nimble/host/services/gatt/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/nimble/host/services/ias/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/nimble/host/services/lls/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/nimble/host/services/tps/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/nimble/host/util/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/nimble/host/store/ram/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/nimble/host/store/config/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/porting/npl/freertos/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/nimble/ext/tinycrypt/include -I/mnt/c/dev/esp-idf/components/bt/host/nimble/esp-hci/include -I../../modules/tensorflow -I../../../tensorflow/tensorflow/lite/micro/tools/make/downloads/flatbuffers/include -Iboards/GENERIC -I../../modules/tensorflow/gemmlowp -I../../modules/tensorflow/ruy -c \
		-o $outputfile \
		$file \
		&

	# wait after every 8
	let file_index+=1
	if ! (( file_index % 8 )); then
		wait
	fi
done

wait 

make USER_C_MODULES=../../modules \
 'CFLAGS_EXTRA=-DMODULE_QUADRATURE_ENABLED=1 -DMODULE_TENSORFLOW_ENABLED=1' \
 all -j8
