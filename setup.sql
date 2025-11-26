-- OpenEarthGenomes adatbázis inicializálása
-- Használat: mysql -u root -p < setup.sql

-- Adatbázis létrehozása
CREATE DATABASE IF NOT EXISTS EarthGenomes 
    CHARACTER SET utf8mb4 
    COLLATE utf8mb4_unicode_ci;

USE EarthGenomes;

-- Genomes tábla létrehozása
CREATE TABLE IF NOT EXISTS genomes (
    id INT AUTO_INCREMENT PRIMARY KEY,
    species_name VARCHAR(255) NOT NULL,
    common_name VARCHAR(255),
    sequence LONGTEXT NOT NULL,
    file_source VARCHAR(500),
    upload_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    sequence_length BIGINT NOT NULL,
    checksum VARCHAR(64),
    
    -- Indexek a gyors kereséshez
    INDEX idx_species (species_name),
    INDEX idx_common (common_name),
    INDEX idx_length (sequence_length),
    INDEX idx_upload_date (upload_date)
    
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Statisztikák tábla (opcionális)
CREATE TABLE IF NOT EXISTS genome_stats (
    id INT AUTO_INCREMENT PRIMARY KEY,
    total_genomes INT DEFAULT 0,
    total_species INT DEFAULT 0,
    total_base_pairs BIGINT DEFAULT 0,
    last_updated DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Kezdő statisztika rekord
INSERT INTO genome_stats (total_genomes, total_species, total_base_pairs) 
VALUES (0, 0, 0) 
ON DUPLICATE KEY UPDATE id=id;

-- User létrehozása (opcionális, biztonsági okokból)
-- CREATE USER IF NOT EXISTS 'genome_user'@'localhost' IDENTIFIED BY 'secure_password';
-- GRANT SELECT, INSERT, UPDATE, DELETE ON EarthGenomes.* TO 'genome_user'@'localhost';

-- Példa adatok beszúrása (teszt célra)
INSERT INTO genomes (species_name, common_name, sequence, file_source, sequence_length) VALUES
('Triticum aestivum', 'Búza', 
 'ATCGATCGATCGATCGATCGATCGATCGATCGATCGATCGATCGATCGATCGATCGATCG', 
 'sample_data.fasta', 58),
('Apis mellifera', 'Mézelő méh', 
 'GCTAGCTAGCTAGCTAGCTAGCTAGCTAGCTAGCTAGCTAGCTAGCTAGCTAGCTAGCTA', 
 'sample_data.fasta', 58),
('Homo sapiens', 'Ember', 
 'CGATCGATCGATCGATCGATCGATCGATCGATCGATCGATCGATCGATCGATCGATCGAT', 
 'sample_data.fasta', 58)
ON DUPLICATE KEY UPDATE id=id;

-- Trigger a statisztikák automatikus frissítésére
DELIMITER //

CREATE TRIGGER IF NOT EXISTS update_stats_after_insert
AFTER INSERT ON genomes
FOR EACH ROW
BEGIN
    UPDATE genome_stats 
    SET total_genomes = (SELECT COUNT(*) FROM genomes),
        total_species = (SELECT COUNT(DISTINCT species_name) FROM genomes),
        total_base_pairs = (SELECT SUM(sequence_length) FROM genomes)
    WHERE id = 1;
END //

CREATE TRIGGER IF NOT EXISTS update_stats_after_delete
AFTER DELETE ON genomes
FOR EACH ROW
BEGIN
    UPDATE genome_stats 
    SET total_genomes = (SELECT COUNT(*) FROM genomes),
        total_species = (SELECT COUNT(DISTINCT species_name) FROM genomes),
        total_base_pairs = (SELECT SUM(sequence_length) FROM genomes)
    WHERE id = 1;
END //

DELIMITER ;

-- Státusz információ
SELECT 'OpenEarthGenomes adatbázis sikeresen inicializálva!' AS status;
SELECT COUNT(*) AS sample_genomes_count FROM genomes;
