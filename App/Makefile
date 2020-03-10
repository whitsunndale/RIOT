# name of your application
APPLICATION = dust

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/..

# Set this to 1 to enable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Use gpio interrupts
USEMODULE += periph_gpio_irq
# Use xtimer
USEMODULE += xtimer

USEMODULE += stbm271

CFLAGS += -DLOG_LEVEL=LOG_NONE  # disable log output

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include

# Set a custom channel if needed
include $(RIOTMAKE)/default-radio-settings.inc.mk
