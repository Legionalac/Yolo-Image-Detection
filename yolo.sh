#!/bin/bash
time yolo task=detect mode=train \
	data=data.yaml imgsz=640 \
	project=runs/train name='exp' \
	epochs=10 batch=8 optimizer='Adam' \
	model=std_weights/yolov8s.pt \
	device=cpu
LAST_EXP=`ls -w1 runs/train/ | tail -n 1`
cp runs/train/$LAST_EXP/weights/best.pt weights/caps.pt


