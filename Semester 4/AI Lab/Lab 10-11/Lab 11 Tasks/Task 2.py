import pandas as pd
import matplotlib.pyplot as mtp
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler
import numpy as np

data = {
    'vehicle_serial_no': [5, 3, 8, 2, 4, 7, 6, 10, 1, 9],
    'mileage': [150000, 120000, 250000, 80000, 100000, 220000, 180000, 300000, 75000, 280000],
    'fuel_efficiency': [15, 18, 10, 22, 20, 12, 16, 8, 24, 9],
    'maintenance_cost': [5000, 4000, 7000, 2000, 3000, 6500, 5500, 8000, 1500, 7500],
    'vehicle_type': ['SUV', 'Sedan', 'Truck', 'Hatchback', 'Sedan', 'Truck', 'SUV', 'Truck', 'Hatchback', 'SUV']
}

df = pd.DataFrame(data)

df['vehicle_type_encoded'] = df['vehicle_type'].map({'SUV': 0, 'Sedan': 1, 'Truck': 2, 'Hatchback': 3})

x = df[['vehicle_serial_no', 'mileage', 'fuel_efficiency', 'maintenance_cost', 'vehicle_type_encoded']].values

kmeans = KMeans(n_clusters=3, init='k-means++', random_state=42)
y_predict = kmeans.fit_predict(x)

mtp.scatter(x[y_predict == 0, 1], x[y_predict == 0, 3], s=100, c='blue', label='Cluster 1')
mtp.scatter(x[y_predict == 1, 1], x[y_predict == 1, 3], s=100, c='green', label='Cluster 2')
mtp.scatter(x[y_predict == 2, 1], x[y_predict == 2, 3], s=100, c='red', label='Cluster 3')
mtp.scatter(kmeans.cluster_centers_[:, 1], kmeans.cluster_centers_[:, 3], s=300, c='yellow', label='Centroid')
mtp.title('Vehicle Clusters (Without Scaling)')
mtp.xlabel('Mileage')
mtp.ylabel('Maintenance Cost')
mtp.legend()
mtp.show()

scaler = StandardScaler()

x_scaled = x.copy().astype(float)
cols_to_scale = [0, 1, 2, 3]  #
x_scaled[:, cols_to_scale] = scaler.fit_transform(x[:, cols_to_scale])

kmeans = KMeans(n_clusters=3, init='k-means++', random_state=42)
y_predict = kmeans.fit_predict(x_scaled)

mtp.scatter(x[y_predict == 0, 1], x[y_predict == 0, 3], s=100, c='blue', label='Cluster 1')
mtp.scatter(x[y_predict == 1, 1], x[y_predict == 1, 3], s=100, c='green', label='Cluster 2')
mtp.scatter(x[y_predict == 2, 1], x[y_predict == 2, 3], s=100, c='red', label='Cluster 3')
mtp.scatter(kmeans.cluster_centers_[:, 1], kmeans.cluster_centers_[:, 3], s=300, c='yellow', label='Centroid')
mtp.title('Vehicle Clusters (With Scaling, except vehicle_type)')
mtp.xlabel('Mileage')
mtp.ylabel('Maintenance Cost')
mtp.legend()
mtp.show()
