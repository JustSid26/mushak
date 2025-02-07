
import numpy as np 
import pandas as pd 
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, accuracy_score
from sklearn.model_selection import train_test_split
import joblib
from sklearn.preprocessing import LabelEncoder

df=pd.read_csv("D:/Python/NasaHerc 2025/Lidar/output.csv")
X = df.drop(columns=['label'])
y = df['label']
print(y.value_counts())
label_encoder = LabelEncoder()
y_encoded = label_encoder.fit_transform(y)
print(y_encoded)
rf_classifier = RandomForestClassifier(n_estimators=100, random_state=42)
rf_classifier.fit(X, y)
joblib.dump(rf_classifier, 'random_forest_model.pkl')

print("Model exported as 'random_forest_model.pkl'")

label_encoder = LabelEncoder()
label_encoder.fit(['forward', 'forward_left', 'forward_right'])

joblib.dump(label_encoder, 'label_encoder.pkl')
