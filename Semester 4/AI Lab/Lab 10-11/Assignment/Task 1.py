import pandas as pd
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score
from imblearn.over_sampling import SMOTE

df = pd.read_csv('creditcard.csv')

X = df.drop('Class', axis=1)
y = df['Class']

smote = SMOTE(random_state=42)
X_resampled, y_resampled = smote.fit_resample(X, y)

scaler = StandardScaler()
X_scaled = scaler.fit_transform(X_resampled)

X_train, X_test, y_train, y_test = train_test_split(X_scaled, y_resampled, test_size=0.3, random_state=42)

LR = LogisticRegression()
LR.fit(X_train, y_train)
y_pred_lr = LR.predict(X_test)

RF = RandomForestClassifier(random_state=42)
RF.fit(X_train, y_train)
y_pred_rf = RF.predict(X_test)

print("Logistic Regression:-")
print(f"Accuracy: {accuracy_score(y_test, y_pred_lr) * 100:.2f}%")
print(f"Precision: {precision_score(y_test, y_pred_lr) * 100:.2f}%")
print(f"Recall: {recall_score(y_test, y_pred_lr) * 100:.2f}%")
print(f"F1-Score: {f1_score(y_test, y_pred_lr) * 100:.2f}%")

print("\nRandom Forest:-")
print(f"Accuracy: {accuracy_score(y_test, y_pred_rf) * 100:.2f}%")
print(f"Precision: {precision_score(y_test, y_pred_rf) * 100:.2f}%")
print(f"Recall: {recall_score(y_test, y_pred_rf) * 100:.2f}%")
print(f"F1-Score: {f1_score(y_test, y_pred_rf) * 100:.2f}%")
