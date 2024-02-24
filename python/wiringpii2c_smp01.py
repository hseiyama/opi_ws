import wiringpi
import sys
import time

# MPU-6050 I2C address
ADDRESS         = 0x68
# MPU-6050 register address
GYRO_CONFIG     = 0x1B
ACCEL_CONFIG    = 0x1C
ACCEL_XOUT_H    = 0x3B
ACCEL_XOUT_L    = 0x3C
ACCEL_YOUT_H    = 0x3D
ACCEL_YOUT_L    = 0x3E
ACCEL_ZOUT_H    = 0x3F
ACCEL_ZOUT_L    = 0x40
TEMP_OUT_H      = 0x41
TEMP_OUT_L      = 0x42
GYRO_XOUT_H     = 0x43
GYRO_XOUT_L     = 0x44
GYRO_YOUT_H     = 0x45
GYRO_YOUT_L     = 0x46
GYRO_ZOUT_H     = 0x47
GYRO_ZOUT_L     = 0x48
PWR_MGMT_1      = 0x6B
PWR_MGMT_2      = 0x6C
WHO_AM_I        = 0x75

# macro function
def ENDIAN_2B(data):
    return (((data >> 8) & 0xFF) | ((data << 8) & 0xFF00))
def sint16(data):
    return (-(data & 0x8000) | (data & 0x7FFF))

def main():
    # initialize
    # wiringpi.wiringPiSetup()
    i2c = wiringpi.I2C()
    i2cdev = i2c.setupInterface("/dev/i2c-2", ADDRESS)
    if(i2cdev < 0):
        print("Unable to open i2c device.", file=sys.stderr)
        sys.exit(1)

    # MPU-6050 setting
    i2c.writeReg8(i2cdev, GYRO_CONFIG, 0x18)    # FS_SEL=11: 2000 deg/s (full scale range of gyroscopes)
    i2c.writeReg8(i2cdev, ACCEL_CONFIG, 0x18)   # AFS_SEL=11: 16 g (full scale range of accelerometers)
    i2c.writeReg8(i2cdev, PWR_MGMT_1, 0x00)     # SLEEP=0: non sleep mode

    # main process
    while(True):
        accel_x = i2c.readReg16(i2cdev, ACCEL_XOUT_H)
        accel_y = i2c.readReg16(i2cdev, ACCEL_YOUT_H)
        accel_z = i2c.readReg16(i2cdev, ACCEL_ZOUT_H)
        s16_accel_x = sint16(ENDIAN_2B(accel_x))
        s16_accel_y = sint16(ENDIAN_2B(accel_y))
        s16_accel_z = sint16(ENDIAN_2B(accel_z))
        # print("accel(x,y,z) = 0x(%04x, %04x, %04x)" % (accel_x, accel_y, accel_z))
        print("accel(x,y,z) = (%d, %d, %d)" % (s16_accel_x, s16_accel_y, s16_accel_z))

        time.sleep(1)

    sys.exit(0)

if(__name__ == "__main__"):
    main()
