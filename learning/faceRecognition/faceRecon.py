#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import sys,os,dlib,glob,numpy
from skimage import io

if len(sys.argv) != 5:
    print "Usage: ./faceRecon.py <detector-file> <face-model-file> <candidate-path> <inpu-face>"
    exit()

#  detector of face key point
predictor_path = sys.argv[1]
# model of face recongnize
face_rec_model_path = sys.argv[2]
# candidate face folder
faces_folder_path = sys.argv[3]
# need be recongnized face
img_path = sys.argv[4]

# load face detector
detector = dlib.get_frontal_face_detector()
# load face key point detector
sp = dlib.shape_predictor(predictor_path)
# load face reconnize model
facerec = dlib.face_recognition_model_v1(face_rec_model_path)

# win = dlib.image_window()

# list of candidate faces
descriptors = []

# candidates
candidates = []

# 1. traversal all candidate images
# 2. detect faces in image
# 3. detect key points of faces
# 4. compute face descriptor
# 5. convert as array and add descriptor list
for f in glob.glob(os.path.join(faces_folder_path, "*.jpg")):
    print("Processing file: {}".format(f))

    # get filename
    filename = os.path.basename(f)
    candidates.append(filename)

    # read image data
    img = io.imread(f)

    #win.clear_overlay()
    #win.set_image(img)

    # 2. detect faces in image
    dets = detector(img, 1)
    print("Number of faces detected: {}".format(len(dets)))
    for k, d in enumerate(dets):  
        # 3. detect key points of faces
        shape = sp(img, d)

        # win.clear_overlay()
        # win.add_overlay(d)
        # win.add_overlay(shape)

        # 4. compute face descriptor
        face_descriptor = facerec.compute_face_descriptor(img, shape)

        # 5. convert as array and add descriptor list
        v = numpy.array(face_descriptor)  
        descriptors.append(v)

# 1. read test image
# 2. detect faces and key points
# 3. compute descriptor
# 4. compute Euclidean distance
# 5. sort and print candidate's name with the least distance
img = io.imread(img_path)
dets = detector(img, 1)
dist = []
for k, d in enumerate(dets):
    shape = sp(img, d)
    face_descriptor = facerec.compute_face_descriptor(img, shape)
    d_test = numpy.array(face_descriptor)
    # 4. compute Euclidean distance
    for i in descriptors:
        dist_ = numpy.linalg.norm(i-d_test)
        dist.append(dist_)

# list of candidates' name
#candidates = ['Unknown1','Unknown2','Shishi','Unknown4','Bingbing','Feifei']

# make a dictionary from candidate to name
c_d = dict(zip(candidates,dist))
# sort dictionary
cd_sorted = sorted(c_d.iteritems(), key=lambda d:d[1])
print " The person is: ",cd_sorted[0][0]  

#dlib.hit_enter_to_continue()
