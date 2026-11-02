/*
 * BigFont.cpp - Big Font library for Arduino - Version 0.1.0
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
 */

#include "BigFont-for-hd44780.h"

namespace {
// The seven original BigFont segments (slot 7 remains an alarm icon).
// Binary patterns adapted from gcassarino/BigFont, GPL-3.0 repository.
uint8_t glyph2[7][8] = {
 {0,0,0,0,0,31,31,31},
 {7,15,31,31,31,31,31,31},
 {31,31,31,0,0,0,0,0},
 {28,30,31,31,31,31,30,28},
 {31,31,31,31,31,31,15,7},
 {31,0,0,0,0,0,0,31},
 {31,31,31,31,31,31,30,28}
};
uint8_t glyph3[7][8] = {
 {1,3,7,15,31,30,28,24},
 {7,15,31,31,31,31,31,31},
 {31,31,31,0,0,0,0,0},
 {28,30,31,31,31,31,31,31},
 {31,31,31,31,31,31,15,7},
 {0,0,0,0,0,31,31,31},
 {31,31,31,31,31,31,30,28}
};
uint8_t bell[8] = {4,14,14,14,31,0,4,0};

// Segment 254 means empty, 255 means filled CGROM character.
const uint8_t font2[10][2][3] = {
 {{1,2,255},{4,0,6}},
 {{47,255,254},{254,255,254}},
 {{2,5,3},{1,5,0}},
 {{2,5,3},{0,5,3}},
 {{1,254,255},{254,2,6}},
 {{255,5,2},{0,5,3}},
 {{1,2,254},{4,5,3}},
 {{4,2,6},{254,47,254}},
 {{1,5,3},{1,5,3}},
 {{1,2,255},{0,5,6}}
};
const uint8_t font3[10][3][3] = {
 {{1,2,3},{255,254,255},{4,5,6}},
 {{0,255,254},{254,255,254},{5,255,5}},
 {{1,2,3},{254,5,6},{1,5,5}},
 {{1,2,3},{254,2,3},{4,5,6}},
 {{254,0,255},{1,5,6},{254,254,3}},
 {{255,2,2},{2,2,3},{5,5,6}},
 {{1,2,254},{255,2,3},{4,5,6}},
 {{4,2,255},{254,1,6},{254,255,254}},
 {{1,2,3},{1,2,3},{4,5,6}},
 {{1,2,3},{4,5,255},{4,5,6}}
};
const uint8_t font4[10][4][4] = {
 {{1,2,2,3},{255,254,254,255},{255,254,254,255},{4,5,5,6}},
 {{254,1,255,254},{254,254,255,254},{254,254,255,254},{254,5,255,5}},
 {{1,2,2,3},{254,254,5,6},{1,2,254,254},{255,5,5,5}},
 {{1,2,2,3},{254,254,5,6},{254,254,2,3},{4,5,5,6}},
 {{255,254,254,255},{255,254,254,255},{4,5,5,255},{254,254,254,255}},
 {{255,2,2,2},{2,2,2,3},{254,254,254,255},{4,5,5,6}},
 {{1,2,2,254},{255,2,2,3},{255,254,254,255},{4,5,5,6}},
 {{4,2,2,255},{254,254,1,6},{254,254,255,254},{254,254,255,254}},
 {{1,2,2,3},{4,5,5,6},{1,2,2,3},{4,5,5,6}},
 {{1,2,2,3},{255,254,254,255},{4,5,5,255},{254,5,5,6}}
};

void drawCell(hd44780& lcd, uint8_t value) {
  if (value == 254) lcd.write((uint8_t)' ');
  else lcd.write(value);
}
void clearRow(hd44780& lcd, uint8_t row, uint8_t cols) {
  lcd.setCursor(0, row);
  for (uint8_t i = 0; i < cols; ++i) lcd.write((uint8_t)' ');
}
} // namespace

BigFont::BigFont(uint8_t size) : _fontSize(3) { setFontSize(size); }

void BigFont::setFontSize(uint8_t size) {
  _fontSize = size < 2 ? 2 : size > 4 ? 4 : size;
}
uint8_t BigFont::getFontSize() { return _fontSize; }
int BigFont::version(void) { return 2; }

void BigFont::loadchars(hd44780& lcd) {
  uint8_t (*glyphs)[8] = (_fontSize == 2) ? glyph2 : glyph3;
  for (uint8_t i = 0; i < 7; ++i) lcd.createChar(i, glyphs[i]);
  lcd.createChar(7, bell);
}

void BigFont::printblankchar(hd44780& lcd, byte col, byte row) {
  uint8_t width = _fontSize == 4 ? 4 : 3;
  for (uint8_t y = 0; y < _fontSize; ++y) {
    lcd.setCursor(col, row + y);
    for (uint8_t x = 0; x < width; ++x) lcd.write((uint8_t)' ');
  }
}
void BigFont::printbigchar(hd44780& lcd, byte digit, byte col, byte row) {
  if (digit > 9) return;
  uint8_t width = _fontSize == 4 ? 4 : 3;
  for (uint8_t y = 0; y < _fontSize; ++y) {
    lcd.setCursor(col, row + y);
    for (uint8_t x = 0; x < width; ++x) {
      if (_fontSize == 2) drawCell(lcd, font2[digit][y][x]);
      else if (_fontSize == 3) drawCell(lcd, font3[digit][y][x]);
      else drawCell(lcd, font4[digit][y][x]);
    }
  }
}

void BigFont::centerPrint(hd44780& lcd, uint8_t row, const String& text,
                          uint8_t lcdCols) {
  clearRow(lcd, row, lcdCols);
  String out = text.substring(0, lcdCols);
  uint8_t start = (lcdCols - out.length()) / 2;
  lcd.setCursor(start, row);
  lcd.print(out);
}

void BigFont::centerPrintBig(hd44780& lcd, uint8_t row, const String& digits,
                             uint8_t lcdCols) {
  for (uint8_t y = 0; y < _fontSize; ++y) clearRow(lcd, row + y, lcdCols);
  String filtered;
  for (size_t i = 0; i < digits.length(); ++i)
    if (digits[i] >= '0' && digits[i] <= '9') filtered += digits[i];
  uint8_t width = _fontSize == 4 ? 4 : 3;
  uint8_t maxDigits = (lcdCols + 1) / (width + 1);
  if (filtered.length() > maxDigits) filtered = filtered.substring(0, maxDigits);
  if (filtered.length() == 0) return;
  uint8_t total = filtered.length() * width + filtered.length() - 1;
  uint8_t x = (lcdCols - total) / 2;
  for (size_t i = 0; i < filtered.length(); ++i)
    printbigchar(lcd, filtered[i] - '0', x + i * (width + 1), row);
}

bool BigFont::centerPrintClock(hd44780& lcd, uint8_t row, const String& time,
                               uint8_t lcdCols, uint8_t lcdRows) {
  if (_fontSize != 3 || lcdCols < 17 || row + 3 > lcdRows) return false;
  if (time.length() != 5 || time[2] != ':') return false;
  const uint8_t digitPositions[4] = {0, 1, 3, 4};
  for (uint8_t j = 0; j < 4; ++j) {
    uint8_t i = digitPositions[j];
    if (time[i] < '0' || time[i] > '9') return false;
  }
  for (uint8_t y = 0; y < 3; ++y) clearRow(lcd, row + y, lcdCols);
  // 3 + 1 + 3 + 1 + 1 + 1 + 3 + 1 + 3 = 17 LCD columns.
  uint8_t start = (lcdCols - 17) / 2;
  printbigchar(lcd, time[0] - '0', start, row);
  printbigchar(lcd, time[1] - '0', start + 4, row);
  // Use the LCD ROM colon (single 5x8 character), centered vertically.
  lcd.setCursor(start + 8, row + 1);
  lcd.write((uint8_t)':');
  printbigchar(lcd, time[3] - '0', start + 10, row);
  printbigchar(lcd, time[4] - '0', start + 14, row);
  return true;
}
