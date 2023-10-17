from ultralytics import YOLO
# from ultralytics.yolo.utils.benchmarks import benchmark
import cv2

# Load a model
# model = YOLO("yolov8n.yaml")  # build a new model from scratch
model = YOLO("best.pt")  # load a pretrained model (recommended for training)


'''t6
results = model("bus.jpg")  # predict on an image
print(results)
'''
img_path = "datasets/data/train/images"
results = model.predict(img_path, save=True, conf=0.72)  # device=0 by default, conf:置信度阈值
