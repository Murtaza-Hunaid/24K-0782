import pandas as pd
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as mtp
import numpy as np

df = pd.read_csv('Mall_Customers.csv')

df['Genre'] = df['Genre'].map({'Male': 0, 'Female': 1})
x = df.drop('CustomerID', axis=1).values

kmeans = KMeans(n_clusters=5, init='k-means++', random_state=42)
y_predict = kmeans.fit_predict(x)

mtp.scatter(x[y_predict == 0, 2], x[y_predict == 0, 3], s=100, c='blue', label='Cluster 1')
mtp.scatter(x[y_predict == 1, 2], x[y_predict == 1, 3], s=100, c='green', label='Cluster 2')
mtp.scatter(x[y_predict == 2, 2], x[y_predict == 2, 3], s=100, c='red', label='Cluster 3')
mtp.scatter(x[y_predict == 3, 2], x[y_predict == 3, 3], s=100, c='black', label='Cluster 4')
mtp.scatter(x[y_predict == 4, 2], x[y_predict == 4, 3], s=100, c='purple', label='Cluster 5')
mtp.scatter(kmeans.cluster_centers_[:, 2], kmeans.cluster_centers_[:, 3], s=300, c='yellow', label='Centroid')
mtp.title('Clusters of Customers (Without Scaling)')
mtp.xlabel('Annual Income (k$)')
mtp.ylabel('Spending Score (1-100)')
mtp.legend()
mtp.show()

scaler = StandardScaler()

# Columns: Genre=0, Age=1, Annual Income=2, Spending Score=3, scale all except Age (index 1)
x_scaled = x.copy().astype(float)
cols_to_scale = [0, 2, 3]
x_scaled[:, cols_to_scale] = scaler.fit_transform(x[:, cols_to_scale])

kmeans = KMeans(n_clusters=5, init='k-means++', random_state=42)
y_predict = kmeans.fit_predict(x_scaled)

mtp.scatter(x[y_predict == 0, 2], x[y_predict == 0, 3], s=100, c='blue', label='Cluster 1')
mtp.scatter(x[y_predict == 1, 2], x[y_predict == 1, 3], s=100, c='green', label='Cluster 2')
mtp.scatter(x[y_predict == 2, 2], x[y_predict == 2, 3], s=100, c='red', label='Cluster 3')
mtp.scatter(x[y_predict == 3, 2], x[y_predict == 3, 3], s=100, c='black', label='Cluster 4')
mtp.scatter(x[y_predict == 4, 2], x[y_predict == 4, 3], s=100, c='purple', label='Cluster 5')
mtp.scatter(kmeans.cluster_centers_[:, 2], kmeans.cluster_centers_[:, 3], s=300, c='yellow', label='Centroid')
mtp.title('Clusters of Customers (With Scaling, except Age)')
mtp.xlabel('Annual Income (k$)')
mtp.ylabel('Spending Score (1-100)')
mtp.legend()
mtp.show()
