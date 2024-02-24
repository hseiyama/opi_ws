#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

typedef signed short sint16;

/* MPU-6050 I2C address */
#define ADDRESS         (0x68)
/* MPU-6050 register address */
#define GYRO_CONFIG     (0x1B)
#define ACCEL_CONFIG    (0x1C)
#define ACCEL_XOUT_H    (0x3B)
#define ACCEL_XOUT_L    (0x3C)
#define ACCEL_YOUT_H    (0x3D)
#define ACCEL_YOUT_L    (0x3E)
#define ACCEL_ZOUT_H    (0x3F)
#define ACCEL_ZOUT_L    (0x40)
#define TEMP_OUT_H      (0x41)
#define TEMP_OUT_L      (0x42)
#define GYRO_XOUT_H     (0x43)
#define GYRO_XOUT_L     (0x44)
#define GYRO_YOUT_H     (0x45)
#define GYRO_YOUT_L     (0x46)
#define GYRO_ZOUT_H     (0x47)
#define GYRO_ZOUT_L     (0x48)
#define PWR_MGMT_1      (0x6B)
#define PWR_MGMT_2      (0x6C)
#define WHO_AM_I        (0x75)

/* macro function */
#define ENDIAN_2B(data) (((data >> 8) & 0xFF) | ((data << 8) & 0xFF00))

int main(void) {
    /* initialize */
    // wiringPiSetup();
    int i2cdev = wiringPiI2CSetupInterface("/dev/i2c-2", ADDRESS);
    if(i2cdev < 0) {
        fprintf(stderr, "Unable to open i2c device.\n");
        return 1;
    }

    /* MPU-6050 setting */
    wiringPiI2CWriteReg8(i2cdev, GYRO_CONFIG, 0x18);    // FS_SEL=11: 2000 deg/s (full scale range of gyroscopes)
    wiringPiI2CWriteReg8(i2cdev, ACCEL_CONFIG, 0x18);   // AFS_SEL=11: 16 g (full scale range of accelerometers)
    wiringPiI2CWriteReg8(i2cdev, PWR_MGMT_1, 0x00);     // SLEEP=0: non sleep mode

    /* main process */
    while(TRUE) {
        int accel_x = wiringPiI2CReadReg16(i2cdev, ACCEL_XOUT_H);
        int accel_y = wiringPiI2CReadReg16(i2cdev, ACCEL_YOUT_H);
        int accel_z = wiringPiI2CReadReg16(i2cdev, ACCEL_ZOUT_H);
        sint16 s16_accel_x = (sint16)ENDIAN_2B(accel_x);
        sint16 s16_accel_y = (sint16)ENDIAN_2B(accel_y);
        sint16 s16_accel_z = (sint16)ENDIAN_2B(accel_z);
        // printf("accel(x,y,z) = 0x(%04x, %04x, %04x)\n", accel_x, accel_y, accel_z);
        printf("accel(x,y,z) = (%d, %d, %d)\n", s16_accel_x, s16_accel_y, s16_accel_z);

        delay(1000);
    }

    return 0;
}
