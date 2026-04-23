import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score

df = pd.read_csv("emails.csv")
df = df.dropna()

X = df.drop(["Prediction", "Email No."], axis=1)
y = df["Prediction"]

x_train, x_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

DT = DecisionTreeClassifier()
ModelDT = DT.fit(x_train, y_train)

PredictionDT = DT.predict(x_test)

print("Accuracy:", accuracy_score(y_test, PredictionDT))

new_email = pd.DataFrame([X.iloc[0]], columns=X.columns)
print("Spam Prediction:", ModelDT.predict(new_email))
