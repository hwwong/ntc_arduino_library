/*
  NTC.h - Library for temperture measurement.
  Created by HW Wong , November 8, 2015.
  Released into the public domain.
*/

#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

#define LUT_OFFSET -19
/*  Look up table size = 1796 bytes
  3435 NTC with pull up resistor connection ADC temperature look up table in degree C x 1000
  measure rang from -30 deg C to 80 deg C     */

const int16_t NTC3435_LUT[] = {
0xF448, 0xF4AC, 0xF510, 0xF574, 0xF5A6, 0xF5D8, 0xF63C, 0xF6A0, 0xF704, 0xF736, 
0xF768, 0xF7CC, 0xF7FE, 0xF830, 0xF894, 0xF8C6, 0xF8F8, 0xF92A, 0xF95C, 0xF9C0, 
0xF9F2, 0xFA24, 0xFA56, 0xFA88, 0xFABA, 0xFAEC, 0xFB1E, 0xFB50, 0xFB82, 0xFBB4, 
0xFBD5, 0xFBF6, 0xFC18, 0xFC4A, 0xFC7C, 0xFC9D, 0xFCBE, 0xFCE0, 0xFD12, 0xFD44, 
0xFD65, 0xFD86, 0xFDA8, 0xFDC9, 0xFDEA, 0xFE0C, 0xFE2D, 0xFE4E, 0xFE70, 0xFE91, 
0xFEB2, 0xFED4, 0xFEF5, 0xFF16, 0xFF38, 0xFF59, 0xFF7A, 0xFF9C, 0xFFB5, 0xFFCE, 
0xFFE7, 0x0000, 0x0021, 0x0042, 0x0064, 0x007D, 0x0096, 0x00AF, 0x00C8, 0x00E9, 
0x010A, 0x012C, 0x0145, 0x015E, 0x0177, 0x0190, 0x01A9, 0x01C2, 0x01DB, 0x01F4, 
0x020D, 0x0226, 0x023F, 0x0258, 0x0271, 0x028A, 0x02A3, 0x02BC, 0x02D5, 0x02EE, 
0x0307, 0x0320, 0x0334, 0x0348, 0x035C, 0x0370, 0x0384, 0x039D, 0x03B6, 0x03CF, 
0x044C, 0x046D, 0x048E, 0x04B0, 0x04D1, 0x04F2, 0x0514, 0x0528, 0x053C, 0x0550, 
0x0564, 0x0578, 0x058C, 0x05A0, 0x05B4, 0x05C8, 0x05DC, 0x05EC, 0x05FD, 0x060E, 
0x061E, 0x062F, 0x0640, 0x064E, 0x065C, 0x066A, 0x0679, 0x0687, 0x0695, 0x06A4, 
0x06B2, 0x06C0, 0x06CE, 0x06DD, 0x06EB, 0x06F9, 0x0708, 0x0714, 0x0721, 0x072D, 
0x073A, 0x0746, 0x0753, 0x075F, 0x076C, 0x0778, 0x0785, 0x0791, 0x079E, 0x07AA, 
0x07B7, 0x07C3, 0x07D0, 0x07DB, 0x07E6, 0x07F1, 0x07FC, 0x0807, 0x0812, 0x081D, 
0x0828, 0x0834, 0x0840, 0x084D, 0x0859, 0x0866, 0x0872, 0x087F, 0x088B, 0x0898, 
0x08A3, 0x08AE, 0x08B9, 0x08C4, 0x08CF, 0x08DA, 0x08E5, 0x08F0, 0x08FC, 0x0907, 
0x0912, 0x091D, 0x0928, 0x0933, 0x093E, 0x0949, 0x0954, 0x0960, 0x096B, 0x0976, 
0x0981, 0x098C, 0x0997, 0x09A2, 0x09AD, 0x09B8, 0x09C4, 0x09D0, 0x09DD, 0x09E9, 
0x09F6, 0x0A02, 0x0A0F, 0x0A1B, 0x0A28, 0x0A32, 0x0A3C, 0x0A46, 0x0A50, 0x0A5A, 
0x0A64, 0x0A6E, 0x0A78, 0x0A82, 0x0A8C, 0x0A98, 0x0AA5, 0x0AB1, 0x0ABE, 0x0ACA, 
0x0AD7, 0x0AE3, 0x0AF0, 0x0AFB, 0x0B06, 0x0B11, 0x0B1C, 0x0B27, 0x0B32, 0x0B3D, 
0x0B48, 0x0B54, 0x0B5F, 0x0B6A, 0x0B75, 0x0B80, 0x0B8B, 0x0B96, 0x0BA1, 0x0BAC, 
0x0BB8, 0x0BC2, 0x0BCC, 0x0BD6, 0x0BE0, 0x0BEA, 0x0BF4, 0x0BFE, 0x0C08, 0x0C12, 
0x0C1C, 0x0C27, 0x0C32, 0x0C3D, 0x0C48, 0x0C53, 0x0C5E, 0x0C69, 0x0C74, 0x0C80, 
0x0C8B, 0x0C96, 0x0CA1, 0x0CAC, 0x0CB7, 0x0CC2, 0x0CCD, 0x0CD8, 0x0CE4, 0x0CEF, 
0x0CFA, 0x0D05, 0x0D10, 0x0D1B, 0x0D26, 0x0D31, 0x0D3C, 0x0D48, 0x0D52, 0x0D5C, 
0x0D66, 0x0D70, 0x0D7A, 0x0D84, 0x0D8E, 0x0D98, 0x0DA2, 0x0DAC, 0x0DB6, 0x0DC0, 
0x0DCA, 0x0DD4, 0x0DDE, 0x0DE8, 0x0DF2, 0x0DFC, 0x0E06, 0x0E10, 0x0E1A, 0x0E24, 
0x0E2E, 0x0E38, 0x0E42, 0x0E4C, 0x0E56, 0x0E60, 0x0E6A, 0x0E74, 0x0E7E, 0x0E88, 
0x0E92, 0x0E9C, 0x0EA6, 0x0EB0, 0x0EBA, 0x0EC4, 0x0ECE, 0x0ED8, 0x0EE1, 0x0EEA, 
0x0EF3, 0x0EFC, 0x0F05, 0x0F0E, 0x0F17, 0x0F20, 0x0F29, 0x0F32, 0x0F3C, 0x0F45, 
0x0F4E, 0x0F57, 0x0F60, 0x0F69, 0x0F72, 0x0F7B, 0x0F84, 0x0F8D, 0x0F96, 0x0FA0, 
0x0FA9, 0x0FB2, 0x0FBB, 0x0FC4, 0x0FCD, 0x0FD6, 0x0FDF, 0x0FE8, 0x0FF1, 0x0FFA, 
0x1004, 0x100C, 0x1014, 0x101D, 0x1025, 0x102D, 0x1036, 0x103E, 0x1046, 0x104F, 
0x1057, 0x105F, 0x1068, 0x1071, 0x107A, 0x1083, 0x108C, 0x1095, 0x109E, 0x10A7, 
0x10B0, 0x10B9, 0x10C2, 0x10CC, 0x10D4, 0x10DC, 0x10E5, 0x10ED, 0x10F5, 0x10FE, 
0x1106, 0x110E, 0x1117, 0x111F, 0x1127, 0x1130, 0x1137, 0x113F, 0x1147, 0x114E, 
0x1156, 0x115E, 0x1165, 0x116D, 0x1175, 0x117C, 0x1184, 0x118C, 0x1194, 0x119C, 
0x11A4, 0x11AD, 0x11B5, 0x11BD, 0x11C6, 0x11CE, 0x11D6, 0x11DF, 0x11E7, 0x11EF, 
0x11F8, 0x11FF, 0x1207, 0x120F, 0x1216, 0x121E, 0x1226, 0x122D, 0x1235, 0x123D, 
0x1244, 0x124C, 0x1254, 0x125C, 0x1263, 0x126A, 0x1271, 0x1278, 0x127F, 0x1286, 
0x128E, 0x1295, 0x129C, 0x12A3, 0x12AA, 0x12B1, 0x12B8, 0x12C0, 0x12C7, 0x12CF, 
0x12D7, 0x12DE, 0x12E6, 0x12EE, 0x12F5, 0x12FD, 0x1305, 0x130C, 0x1314, 0x131C, 
0x1324, 0x132B, 0x1332, 0x1339, 0x1340, 0x1347, 0x134E, 0x1356, 0x135D, 0x1364, 
0x136B, 0x1372, 0x1379, 0x1380, 0x1388, 0x138E, 0x1395, 0x139C, 0x13A2, 0x13A9, 
0x13B0, 0x13B6, 0x13BD, 0x13C4, 0x13CA, 0x13D1, 0x13D8, 0x13DE, 0x13E5, 0x13EC, 
0x13F2, 0x13F8, 0x13FE, 0x1405, 0x140B, 0x1411, 0x1417, 0x141E, 0x1424, 0x142A, 
0x1430, 0x1437, 0x143D, 0x1443, 0x1449, 0x1450, 0x1456, 0x145D, 0x1464, 0x146A, 
0x1471, 0x1478, 0x147E, 0x1485, 0x148C, 0x1492, 0x1499, 0x14A0, 0x14A6, 0x14AD, 
0x14B4, 0x14BA, 0x14C1, 0x14C8, 0x14CE, 0x14D5, 0x14DC, 0x14E2, 0x14E9, 0x14F0, 
0x14F6, 0x14FD, 0x1504, 0x150A, 0x1511, 0x1518, 0x151D, 0x1523, 0x1529, 0x152F, 
0x1535, 0x153B, 0x1541, 0x1547, 0x154C, 0x1552, 0x1558, 0x155E, 0x1564, 0x156A, 
0x1570, 0x1576, 0x157C, 0x1581, 0x1587, 0x158D, 0x1593, 0x1599, 0x159F, 0x15A5, 
0x15AB, 0x15B0, 0x15B6, 0x15BC, 0x15C2, 0x15C8, 0x15CE, 0x15D4, 0x15DA, 0x15E0, 
0x15E5, 0x15EB, 0x15F1, 0x15F7, 0x15FD, 0x1603, 0x1609, 0x160F, 0x1614, 0x161A, 
0x1620, 0x1626, 0x162C, 0x1632, 0x1638, 0x163E, 0x1644, 0x1649, 0x164E, 0x1653, 
0x1659, 0x165E, 0x1663, 0x1668, 0x166E, 0x1673, 0x1678, 0x167D, 0x1683, 0x1688, 
0x168D, 0x1692, 0x1698, 0x169D, 0x16A2, 0x16A8, 0x16AD, 0x16B2, 0x16B7, 0x16BC, 
0x16C1, 0x16C6, 0x16CB, 0x16D0, 0x16D5, 0x16DA, 0x16DF, 0x16E4, 0x16E9, 0x16EE, 
0x16F3, 0x16F8, 0x16FD, 0x1702, 0x1707, 0x170C, 0x1711, 0x1716, 0x171B, 0x1720, 
0x1725, 0x172A, 0x172F, 0x1734, 0x1739, 0x173E, 0x1743, 0x1748, 0x174D, 0x1752, 
0x1757, 0x175C, 0x1761, 0x1766, 0x176B, 0x1770, 0x177A, 0x1784, 0x178E, 0x1798, 
0x17A2, 0x17AC, 0x17B6, 0x17C0, 0x17CA, 0x17D4, 0x17DD, 0x17E6, 0x17EF, 0x17F8, 
0x1801, 0x180A, 0x1813, 0x181C, 0x1825, 0x182E, 0x1838, 0x183E, 0x1845, 0x184C, 
0x1852, 0x1859, 0x1860, 0x1866, 0x186D, 0x1874, 0x187A, 0x1881, 0x1888, 0x188E, 
0x1895, 0x189C, 0x18A3, 0x18AA, 0x18B1, 0x18B8, 0x18BF, 0x18C6, 0x18CE, 0x18D5, 
0x18DC, 0x18E3, 0x18EA, 0x18F1, 0x18F8, 0x1900, 0x1906, 0x190C, 0x1912, 0x1919, 
0x191F, 0x1925, 0x192B, 0x1932, 0x1938, 0x193E, 0x1944, 0x194B, 0x1951, 0x1957, 
0x195D, 0x1964, 0x1969, 0x196F, 0x1974, 0x197A, 0x197F, 0x1985, 0x198A, 0x1990, 
0x1996, 0x199B, 0x19A1, 0x19A6, 0x19AC, 0x19B1, 0x19B7, 0x19BC, 0x19C2, 0x19C8, 
0x19CD, 0x19D3, 0x19D9, 0x19DF, 0x19E5, 0x19EB, 0x19F1, 0x19F7, 0x19FC, 0x1A02, 
0x1A08, 0x1A0E, 0x1A14, 0x1A1A, 0x1A20, 0x1A26, 0x1A2C, 0x1A30, 0x1A35, 0x1A3A, 
0x1A3F, 0x1A43, 0x1A48, 0x1A4D, 0x1A52, 0x1A56, 0x1A5B, 0x1A60, 0x1A65, 0x1A69, 
0x1A6E, 0x1A73, 0x1A78, 0x1A7C, 0x1A81, 0x1A86, 0x1A8B, 0x1A90, 0x1A95, 0x1A9A, 
0x1A9F, 0x1AA5, 0x1AAA, 0x1AAF, 0x1AB4, 0x1ABA, 0x1ABF, 0x1AC4, 0x1AC9, 0x1ACF, 
0x1AD4, 0x1AD9, 0x1ADE, 0x1AE4, 0x1AE9, 0x1AEE, 0x1AF4, 0x1AF9, 0x1AFE, 0x1B03, 
0x1B09, 0x1B0E, 0x1B13, 0x1B18, 0x1B1E, 0x1B23, 0x1B28, 0x1B2D, 0x1B33, 0x1B38, 
0x1B3D, 0x1B42, 0x1B48, 0x1B4D, 0x1B52, 0x1B58, 0x1B5C, 0x1B61, 0x1B66, 0x1B6B, 
0x1B6F, 0x1B74, 0x1B79, 0x1B7E, 0x1B82, 0x1B87, 0x1B8C, 0x1B91, 0x1B95, 0x1B9A, 
0x1B9F, 0x1BA4, 0x1BA8, 0x1BAD, 0x1BB2, 0x1BB7, 0x1BBC, 0x1BC0, 0x1BC5, 0x1BC9, 
0x1BCE, 0x1BD2, 0x1BD7, 0x1BDB, 0x1BE0, 0x1BE4, 0x1BE9, 0x1BEE, 0x1BF2, 0x1BF7, 
0x1BFB, 0x1C00, 0x1C04, 0x1C09, 0x1C0D, 0x1C12, 0x1C16, 0x1C1B, 0x1C20, 0x1C25, 
0x1C2A, 0x1C2F, 0x1C34, 0x1C39, 0x1C3E, 0x1C43, 0x1C48, 0x1C4D, 0x1C52, 0x1C57, 
0x1C5C, 0x1C61, 0x1C66, 0x1C6B, 0x1C70, 0x1C75, 0x1C7A, 0x1C7F, 0x1C84, 0x1C89, 
0x1C8E, 0x1C93, 0x1C98, 0x1C9D, 0x1CA2, 0x1CA7, 0x1CAC, 0x1CB1, 0x1CB6, 0x1CBB, 
0x1CC0, 0x1CC5, 0x1CCA, 0x1CCF, 0x1CD4, 0x1CD9, 0x1CDE, 0x1CE3, 0x1CE8, 0x1CEC, 
0x1CF1, 0x1CF5, 0x1CFA, 0x1CFE, 0x1D03, 0x1D07, 0x1D0C, 0x1D10, 0x1D15, 0x1D1A, 
0x1D1E, 0x1D23, 0x1D27, 0x1D2C, 0x1D30, 0x1D35, 0x1D39, 0x1D3E};

class NTC
{
  public:
	NTC(int pin);
	int16_t readTemperature();
  private:
	int _pin;


};

#endif

