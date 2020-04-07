/* 
 * File:   button.h
 * Author: dima_ses
 *
 * Created on September 20, 2019, 7:26 PM
 */

#ifndef BUTTON_H
#define BUTTON_GPIO PD3
#define BUTTON_DDR DDRD
#define BUTTON_PIN PIND
#define BUTTON_PORT PORTD

#define F_CPU 8000000UL
#include "main.h"
void Btn_init();    //������������� 
uint8_t Read_btn(void); //���������� ��������� ���� ������
uint8_t Btn_press(void);    //���� ������ ���� ������
uint8_t Btn_release(void);  //���� ������ ���� ��������
uint8_t Btn_hold(void); //���� ������ ������������ ����� 1�
uint8_t Btn_double_press(void);   //������� �������
void Reset_btn_press_count(void);   //����� �������� �������, ���� �� �������� ������ ���
void Btn_handler(void); //������� ��� ��������� ������� ������ ���������� � �������� 10��
#endif	/* BUTTON_H */

