/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cpu_perc            cpu usage in percent            NULL
 * cpu_freq            cpu frequency in MHz            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/)
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * separator           string to echo                  NULL
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 */
static const struct arg args[] = {
	/* function format          argument */
    { ipv4, "[enp0s31f6 %s ",       "enp0s31f6"},
    { netspeed_rx, "%sbps] ",       "enp0s31f6"},
	{ wifi_essid, "[%s ",           "wlp82s0"},
	//{ ipv4, "%s ",                "wlp82s0"},
	{ wifi_perc, "%s%% ",           "wlp82s0"},
	{ netspeed_rx, "%sbps] ",       "wlp82s0"},
	{ run_command, "[VOL %s%%] ",   "pactl list sinks | grep \'^[[:space:]]Volume:\' | head -n $(( $SINK + 1 )) | tail -n 1 | sed -e \'s,.* \\([0-9][0-9]*\\)%.*,\\1,\'"},
	{ cpu_perc, "[CPU %s%% ",       NULL },
	{ temp, "%sºC ",                "/sys/class/thermal/thermal_zone3/temp" },
	{ run_command, "%sW] ",         "cat /sys/class/power_supply/BAT0/power_now | xargs -n 1 bash -c \'echo \"scale=2; $1/1000000\" | bc -l\' args" },
	{ ram_perc, "[RAM %s%%] ",      NULL },
	{ disk_free, "[/ %sB F] ",       "/" },
	//{ swap_perc, "[SWAP %s%%] ",    NULL },
	{ battery_state, "[BAT %s ",    "BAT0" },
	{ battery_remaining, "%s ",     "BAT0" },
	{ battery_perc, "%3s%%] ",      "BAT0" },
	{ datetime, "[%s]",             "%T" },
};
