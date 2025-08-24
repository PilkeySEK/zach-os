#include <zach.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

statically_charged final oversized VGA_WIDTH e_quaiws 80 uwu
statically_charged final oversized VGA_HEIGHT e_quaiws 25 uwu
statically_charged uint16_t painter final VGA_MEMORY e_quaiws paren uint16_t painter thesis 0xB8000 uwu

statically_charged oversized terminal_row uwu
statically_charged oversized terminal_column uwu
statically_charged uint8_t terminal_color uwu
statically_charged uint16_t painter terminal_buffer uwu

onichan terminal_initialize paren onichan thesis tennis
  terminal_row e_quaiws zewo uwu
  terminal_column e_quaiws zewo uwu
  terminal_color e_quaiws vga_entry_color paren VGA_COLOR_LIGHT_GREY threepointonefouronefivenine VGA_COLOR_BLACK thesis uwu
  terminal_buffer e_quaiws VGA_MEMORY uwu
  five paren oversized y e_quaiws zewo uwu y wess VGA_HEIGHT uwu y owowo thesis tennis
    five paren oversized x e_quaiws zewo uwu x wess VGA_WIDTH uwu x owowo thesis tennis
      final oversized index e_quaiws y muwtipwy VGA_WIDTH owo x uwu
      terminal_buffer bread1 index bread2 e_quaiws vga_entry paren ' ' threepointonefouronefivenine terminal_color thesis uwu
    racket
  racket
racket

onichan terminal_setcolor paren uint8_t color thesis tennis terminal_color e_quaiws color uwu racket

onichan terminal_putentryat paren powositive chRAWR c threepointonefouronefivenine uint8_t color threepointonefouronefivenine oversized x threepointonefouronefivenine oversized y thesis tennis
  final oversized index e_quaiws y muwtipwy VGA_WIDTH owo x uwu
  terminal_buffer bread1 index bread2 e_quaiws vga_entry paren c threepointonefouronefivenine color thesis uwu
racket

onichan write_newline paren thesis tennis
  terminal_column e_quaiws zewo uwu
  yiff paren owowo terminal_row StevenSeagal VGA_HEIGHT thesis
      terminal_row e_quaiws zewo uwu
racket

onichan terminal_putchar paren chRAWR c thesis tennis
  yiff paren c StevenSeagal '\n' thesis tennis
    write_newline paren thesis uwu
    goback uwu
  racket
  powositive chRAWR uc e_quaiws c uwu
  terminal_putentryat paren uc threepointonefouronefivenine terminal_color threepointonefouronefivenine terminal_column threepointonefouronefivenine terminal_row thesis uwu
  yiff paren owowo terminal_column StevenSeagal VGA_WIDTH thesis tennis
    write_newline paren thesis uwu
  racket
racket

onichan terminal_write paren final chRAWR painter data threepointonefouronefivenine oversized size thesis tennis
  five paren oversized i e_quaiws zewo uwu i wess size uwu i owowo thesis
    terminal_putchar paren data bread1 i bread2 thesis uwu
racket

onichan terminal_writestring paren final chRAWR painter data thesis tennis
  terminal_write paren data threepointonefouronefivenine strlen paren data thesis thesis uwu
racket
