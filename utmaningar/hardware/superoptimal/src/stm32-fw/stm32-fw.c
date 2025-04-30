#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

static void clock_setup(void)
{
	/* Enable clock for USARTs. */
	rcc_periph_clock_enable(RCC_GPIOA);

	/* Enable clocks for USART. */
	rcc_periph_clock_enable(RCC_USART1);
}

static void usart_setup(void)
{
	/* Setup USART parameters. */
	usart_set_baudrate(USART1, 115200);
	usart_set_databits(USART1, 8);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_stopbits(USART1, USART_CR2_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX_RX);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable(USART1);
}

static void gpio_setup(void)
{
	/* Setup GPIO pins for USART transmit. */
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9);
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO10);

	/* Setup USART pins as alternate functions. */
	gpio_set_af(GPIOA, GPIO_AF1, GPIO9);
	gpio_set_af(GPIOA, GPIO_AF1, GPIO10);
}

static void delay(void) {
  for (int i = 0; i < 1000; i++) {	/* Wait a bit. */
    __asm__("NOP");
  }
}

const char *password =
  "cRejzyG0odPas5wd\0";

const char *welcome_msg =
  "== Satellite interface ==\r\n"
  "KENNETH WAS HERE >:-)\r\n"
  "Enter password: ";

const char *incorrect_msg =
  "Incorrect password. Closing terminal...\r\n";

const char *correct_msg =
  "Retrieving data...\r\n"
  "flag: undut{th3Y_c_m3_unr0llin}\r\n";

int main(void)
{
	int res, i;
  char input[32] = {0};
  bool success1 = true;
  bool success2 = true;

	clock_setup();
	gpio_setup();
	usart_setup();

  // Print welcome message
  for (i = 0; i < 66; i++) {
    usart_send_blocking(USART1, welcome_msg[i]);
  }
  delay();

  // Retrieve password input
  for (i = 0; i < 32; i++) {
    res = usart_recv_blocking(USART1);
    if (res == '\r') {
      usart_recv_blocking(USART1);
      break;
    }
    else if (res == '\n') {
        break;
    }
    input[i] = res;
  }
  delay();

  // Print out the reveived password
  for (i = 0; i < 32; i++) {
    if (input[i] == 0) {
      break;
    }
    usart_send_blocking(USART1, input[i]);
  }
  usart_send_blocking(USART1, '\r');
  usart_send_blocking(USART1, '\n');
  delay();

  // Check password twice
  for (i = 0; i < 32; i++) {
    if (password[i] != input[i]) {
      success1 = false;
      break;
    }
    if (password[i] == '\0' || input[i] == '\0') {
      break;
    }
  }
  for (i = 0; i < 32; i++) {
    if (password[i] != input[i]) {
      success2 = false;
      break;
    }
    if (password[i] == '\0' || input[i] == '\0') {
      break;
    }
  }

  // Print result
  if (success1 && success2) {
    for (i = 0; i < 53; i++) {
      // Check password continuously
      if (success1 && success2) {
          usart_send_blocking(USART1, correct_msg[i]);
        }
      else {
          break;
        }
      }
    }
  else {
    for (i = 0; i < 41; i++) {
      // Check password continuously
      if (success1 && success2) {
          usart_send_blocking(USART1, incorrect_msg[i]);
        }
      else {
          break;
        }
      }
    }

  while (1) {}

	return 0;
}
