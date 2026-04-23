import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score, mean_squared_error

df = pd.read_csv("/content/sample_data/california_housing_test.csv")

df = df.dropna()

X = df.drop("median_house_value", axis=1)
y = df["median_house_value"]

x_train, x_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

LR = LinearRegression()
ModelLR = LR.fit(x_train, y_train)

PredictionLR = ModelLR.predict(x_test)

print("R2 Score:", r2_score(y_test, PredictionLR))

rmse = np.sqrt(mean_squared_error(y_test, PredictionLR))
print("RMSE:", rmse)

new_house = pd.DataFrame([X.iloc[0]], columns=X.columns)
print("Predicted Price:", ModelLR.predict(new_house))
