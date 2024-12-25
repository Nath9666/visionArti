import os
import numpy as np
import cv2
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.callbacks import ModelCheckpoint

# Chemins des données
data_dir = '../data/images'
model_save_path = '../models/trained_model.h5'

# Prétraitement des images
def preprocess_images(image_path):
    image = cv2.imread(image_path)
    image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)  # Conversion en niveaux de gris
    image = cv2.resize(image, (64, 64))  # Redimensionnement
    image = image / 255.0  # Normalisation
    return image

# Chargement des données
def load_data(data_dir):
    images = []
    labels = []
    for label in os.listdir(data_dir):
        label_dir = os.path.join(data_dir, label)
        for image_file in os.listdir(label_dir):
            image_path = os.path.join(label_dir, image_file)
            image = preprocess_images(image_path)
            images.append(image)
            labels.append(label)
    return np.array(images), np.array(labels)

# Création du modèle
def create_model():
    model = Sequential()
    model.add(Conv2D(32, (3, 3), activation='relu', input_shape=(64, 64, 1)))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Flatten())
    model.add(Dense(128, activation='relu'))
    model.add(Dense(len(set(labels)), activation='softmax'))  # Nombre de classes
    model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    return model

# Entraînement du modèle
def train_model():
    images, labels = load_data(data_dir)
    images = images.reshape(-1, 64, 64, 1)  # Reshape pour le modèle
    datagen = ImageDataGenerator(validation_split=0.2)
    
    model = create_model()
    
    checkpoint = ModelCheckpoint(model_save_path, save_best_only=True, monitor='val_loss', mode='min')
    
    model.fit(datagen.flow(images, labels, subset='training'),
              validation_data=datagen.flow(images, labels, subset='validation'),
              epochs=10,
              callbacks=[checkpoint])

if __name__ == "__main__":
    train_model()