#!/bin/bash
yolo predict \
  model=weights/last.pt \
	source=datasets/test/images \
	imgsz=640 \
  save=True \
  save_txt=True
	


