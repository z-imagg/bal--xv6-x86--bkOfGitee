set $lastcs = -1

set logging file /crk/xv6-x86/gdb_log.txt
set logging on

set print pretty on
set pagination off


define hook-stop
  # There doesn't seem to be a good way to detect if we're in 16- or
  # 32-bit mode, but in 32-bit mode we always run with CS == 8 in the
  # kernel and CS == 35 in user space
  if $cs == 8 || $cs == 35
    if $lastcs != 8 && $lastcs != 35
      set architecture i386
    end
    x/i $pc
  else
    if $lastcs == -1 || $lastcs == 8 || $lastcs == 35
      set architecture i8086
    end
    # Translate the segment:offset into a physical address
    printf "[%4x:%4x] ", $cs, $eip
    x/i $cs*16+$eip
  end
  set $lastcs = $cs
end

echo + target remote localhost:26000\n
target remote localhost:26000

echo + symbol-file kernel\n
symbol-file kernel

break if (*(int*)(0x7c00-16))=0xBB77
commands
	x /2w 0x7c00-32
	continue
end

continue
