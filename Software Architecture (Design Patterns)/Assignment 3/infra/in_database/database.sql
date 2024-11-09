DROP TABLE IF EXISTS units;
CREATE TABLE units (
  id CHAR(64),
  name CHAR(64)
);
DROP TABLE IF EXISTS products;
CREATE TABLE products (
  id CHAR(64),
  unit_id CHAR(64),
  name CHAR(64),
  barcode CHAR(64),
  price INTEGER
);
DROP TABLE IF EXISTS receipt_products;
CREATE TABLE receipt_products (
  receipt_id CHAR(64),
  product_id CHAR(64),
  amount INTEGER
);
DROP TABLE IF EXISTS receipts;
CREATE TABLE receipts (
  receipt_id CHAR(64),
  status TEXT CHECK(status IN ('open', 'closed')) NOT NULL,
  n_products INTEGER,
  total INTEGER
);