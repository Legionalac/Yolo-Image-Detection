from shapely.geometry import box

def calculateIOU(l, p):
    labeledBox = box(l[0], l[1], l[2], l[3])
    predictedBox = box(p[0], p[1], p[2], p[3])
    intersection = labeledBox.intersection(predictedBox).area
    union = predictedBox.area + labeledBox.area - intersection 
    iou = intersection/union
    return iou


counter = 81
f = open("resaults.txt","w")
while counter < 193:
    labelPath = "datasets/valid/labels/{:03d}.txt"
    predictedPath = "runs/detect/predict4/labels/{:03d}.txt"
    label = open(labelPath.format(counter), "r")
    predicted = open(predictedPath.format(counter), "r")

    l = []
    p = []

    for line in label:
        data = line.split(" ")
        l.append([float(data[1]), float(data[2]), float(data[3]) +
                 float(data[1]), float(data[4]) + float(data[2])])
    for line in predicted:
        data = line.split(" ")
        p.append([float(data[1]), float(data[2]), float(data[3]) +
                 float(data[1]), float(data[4]) + float(data[2])])

    predictedCopy = p.copy()
    correct = 0
    for x in p:
        max = -1
        maxElement = -1
        for y in l:
            iou = calculateIOU(x, y)
            if max < iou:
                max = iou
                maxElement = y
        if maxElement != -1 and max>0.5:
            l.remove(maxElement)
            correct +=1
    if len(p) > 0:
        precision = correct/len(p) * 100
        f.write(f"file: {counter}  precision : {precision}\n")
    counter+=1
