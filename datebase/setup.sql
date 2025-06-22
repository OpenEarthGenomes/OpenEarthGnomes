CREATE DATABASE IF NOT EXISTS EarthGenomes;
USE EarthGenomes;

CREATE TABLE Species (
    id INT AUTO_INCREMENT PRIMARY KEY,
    common_name VARCHAR(100) NOT NULL,
    scientific_name VARCHAR(100) NOT NULL,
    genome LONGTEXT NOT NULL
);
