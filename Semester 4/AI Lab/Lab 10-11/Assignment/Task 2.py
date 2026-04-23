import pandas as pd
import numpy as np
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeRegressor
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_absolute_error, mean_squared_error

df = pd.read_csv('train.csv')

for col in df.columns:
  if df[col].dtype == 'object':
    df[col] = df[col].fillna(df[col].mode()[0])
  else:
    df[col] = df[col].fillna(df[col].median())

df = pd.get_dummies(df, drop_first=True)

X = df.drop('SalePrice', axis=1)
y = df['SalePrice']

scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

x_train, x_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.3, random_state=42)

LR = LinearRegression()
ModelLR = LR.fit(x_train, y_train)
PredictionLR = ModelLR.predict(x_test)

print('Linear Regression:-')
print(f"MAE: {mean_absolute_error(y_test, PredictionLR):.2f}")
print(f"RMSE: {np.sqrt(mean_squared_error(y_test, PredictionLR)):.2f}")
print("\nPredicted vs Actual (first 10):")
comparison_lr = pd.DataFrame({'Actual': y_test.values[:10], 'Predicted': PredictionLR[:10].round(2)})
print(comparison_lr.to_string(index=False))

DT = DecisionTreeRegressor(random_state=42)
ModelDT = DT.fit(x_train, y_train)
PredictionDT = ModelDT.predict(x_test)

print('\nDecision Tree Regressor:-')
print(f"MAE: {mean_absolute_error(y_test, PredictionDT):.2f}")
print(f"RMSE: {np.sqrt(mean_squared_error(y_test, PredictionDT)):.2f}")
print("\nPredicted vs Actual (first 10):")
comparison_dt = pd.DataFrame({'Actual': y_test.values[:10], 'Predicted': PredictionDT[:10].round(2)})
print(comparison_dt.to_string(index=False))
