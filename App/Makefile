# name of your application
APPLICATION = dust

# If no BOARD is found in the environment, use this default:
BOARD ?= esp32-wroom-32

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

# Enable wifi on ESP32
USEMODULE += esp_wifi
# Include credentials
include $(CURDIR)/creds.mk


# Include packages that pull up and auto-init the link layer.
# NOTE: 6LoWPAN will be included if IEEE802.15.4 devices are present
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_icmpv6
# Activate ICMPv6 error messages
USEMODULE += gnrc_icmpv6_error
# Specify the mandatory networking modules for IPv6 and UDP
USEMODULE += gnrc_ipv6_default
USEMODULE += gnrc_udp
USEMODULE += gnrc_sock_udp
# This application dumps received packets to STDIO using the pktdump module
USEMODULE += gnrc_pktdump
# Additional networking modules that can be dropped if not needed
USEMODULE += gnrc_icmpv6_echo

USEMODULE += posix_sockets
USEMODULE += posix_time
USEMODULE += posix_inet

CFLAGS += -DLOG_LEVEL=LOG_NONE  # disable log output
CFLAGS += -DGNRC_PKTBUF_SIZE=512 -DCONFIG_GNRC_NETIF_IPV6_ADDRS_NUMOF=2 \
          -DGNRC_NETIF_IPV6_GROUPS_NUMOF=2 -DGNRC_IPV6_NIB_NUMOF=1

# Change Server address using this model :
# CFLAGS += -DSERVER_ADDR=\"fe80\:\:9b95\:29e9\:e279\:a5bd\"

# Change Server port using this model :
# CFLAGS += -DSERVER_PORT=\"8089\"

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include

# Set a custom channel if needed
include $(RIOTMAKE)/default-radio-settings.inc.mk
