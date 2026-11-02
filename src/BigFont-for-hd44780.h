/*
 * BigFont-for-hd44780.h - Big Font library for Arduino - Version 0.1.0
 *
 * Derived from https://github.com/gcassarino/BigFont
 *   Original library   by Gianluca Cassarino
 *   Modified           by Nathan Watson
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Drives 4 row, character type Liquid Crystal Displays with 3x2, 3x3, 4x4 fonts of special symbols
 *
 */

#pragma once

#include <Arduino.h>
#include <hd44780.h>

// hd44780-native adaptation of gcassarino/BigFont for HD44780 character LCDs.
// Copyright of original font design remains with its respective authors.
class BigFont {
 public:
  explicit BigFont(uint8_t size = 3);
  void loadchars(hd44780& lcd);
  void printblankchar(hd44780& lcd, byte col, byte row);
  void printbigchar(hd44780& lcd, byte digit, byte col, byte row);
  uint8_t getFontSize();
  void setFontSize(uint8_t size);
  int version(void);

  // Standard one-row centered string. Clears that row before drawing.
  void centerPrint(hd44780& lcd, uint8_t row, const String& text,
                   uint8_t lcdCols = 20);
  // Large centered digits, 3x2/3x3/4x4 depending on selected font size.
  void centerPrintBig(hd44780& lcd, uint8_t row, const String& digits,
                      uint8_t lcdCols = 20);
  // 3x3 HH:MM clock, preserving leading zero; clears ONLY the clock rows.
  // Returns false for an invalid time string or insufficient display space.
  bool centerPrintClock(hd44780& lcd, uint8_t row, const String& time,
                        uint8_t lcdCols = 20, uint8_t lcdRows = 4);

 private:
  uint8_t _fontSize;
};
