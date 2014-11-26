#!/system/bin/sh
if [ ! -f /data/.shift/efsbackup.tar.gz ];
then
  mkdir /data/.shift
  chmod 777 /data/.shift
  /sbin/busybox tar zcvf /data/.shift/efsbackup.tar.gz /efs
  /sbin/busybox cat /dev/block/mmcblk0p1 > /data/.shift/efsdev-mmcblk0p1.img
  /sbin/busybox gzip /data/.shift/efsdev-mmcblk0p1.img
  #make sure that sdcard is mounted, media scanned..etc
  (
    sleep 500
    /sbin/busybox cp /data/.shift/efs* /storage/sdcard1
  ) &
fi
