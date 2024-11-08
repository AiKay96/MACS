package BasicStore;

public class Product {
    String productID;
    String productName;
    String imageFile;
    double price;

    public Product(String productID, String productName, String imageFile, double price){
        this.productID = productID;
        this.productName = productName;
        this.price = price;
        this.imageFile = imageFile;
    }
    public String getProductID(){
        return productID;
    }
    public String getProductName(){
        return productName;
    }
    public double getPrice(){
        return price;
    }
    public String getImageFile(){
        return imageFile;
    }

}
