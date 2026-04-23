import pandas as pd
import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

df = pd.read_csv("customer_data.csv")
df = df.dropna()

if "name" in df.columns:
    df = df.drop("name", axis=1)

df = pd.get_dummies(df, columns=["gender", "education", "country"], drop_first=True)

df["Customer_Type"] = (df["spending"] > df["spending"].median()).astype(int)

X = df.drop("Customer_Type", axis=1)
y = df["Customer_Type"]

scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)

model = SVC(kernel="linear")
model.fit(X_train, y_train)

y_pred = model.predict(X_test)

print("Accuracy:", accuracy_score(y_test, y_pred))
print("\nConfusion Matrix:\n", confusion_matrix(y_test, y_pred))
print("\nClassification Report:\n", classification_report(y_test, y_pred))

print("\nHyperplane Weights:")
print(model.coef_)

print("\nIntercept:")
print(model.intercept_)
