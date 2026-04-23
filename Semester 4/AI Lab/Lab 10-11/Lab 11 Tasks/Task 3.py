import pandas as pd
import matplotlib.pyplot as mtp
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler

data = {
    'student_id': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
    'GPA': [3.8, 2.5, 1.9, 3.5, 2.1, 3.9, 1.5, 2.8, 3.2, 1.7, 3.6, 2.3, 3.0, 1.8, 2.6],
    'study_hours': [20, 10, 5, 18, 7, 22, 3, 12, 16, 4, 19, 8, 14, 6, 11],
    'attendance_rate': [95, 70, 50, 90, 55, 98, 40, 72, 85, 45, 92, 60, 80, 48, 68]
}
df = pd.DataFrame(data)

x = df[['GPA', 'study_hours', 'attendance_rate']].values
scaler = StandardScaler()
x_scaled = scaler.fit_transform(x)

wcss_list = []
for i in range(2, 7):
  kmeans = KMeans(n_clusters=i, init='k-means++', random_state=42)
  kmeans.fit(x_scaled)
  wcss_list.append(kmeans.inertia_)

mtp.plot(range(2, 7), wcss_list)
mtp.title('The Elbow Method Graph')
mtp.xlabel('Number of clusters (k)')
mtp.ylabel('wcss_list')
mtp.show()

kmeans = KMeans(n_clusters=3, init='k-means++', random_state=42)
y_predict = kmeans.fit_predict(x_scaled)
df['Cluster'] = y_predict

print(df[['student_id', 'GPA', 'study_hours', 'attendance_rate', 'Cluster']])

mtp.scatter(df['study_hours'][y_predict == 0], df['GPA'][y_predict == 0], s=100, c='blue', label='Cluster 1')
mtp.scatter(df['study_hours'][y_predict == 1], df['GPA'][y_predict == 1], s=100, c='green', label='Cluster 2')
mtp.scatter(df['study_hours'][y_predict == 2], df['GPA'][y_predict == 2], s=100, c='red', label='Cluster 3')
mtp.title('Student Clusters based on Academic Engagement')
mtp.xlabel('Study Hours (per week)')
mtp.ylabel('GPA')
mtp.legend()
mtp.show()
