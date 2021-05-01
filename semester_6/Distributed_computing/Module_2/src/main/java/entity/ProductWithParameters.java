package entity;

import javax.sql.RowSet;
import java.io.Serializable;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ProductWithParameters implements Serializable {
    Product product;
    Map<String, String> parametes;

    public static ProductWithParameters parseProduct(RowSet rs) {
        try {

            int id = rs.getInt(1);
            String name = rs.getString(2);
            String description = rs.getString(4);
            int groupId = rs.getInt(3);
            Timestamp time = rs.getTimestamp(5);
            Product p = new Product(id, name, groupId, description, time);
            Map<String, String> parameters = new HashMap<>();
            String s = rs.getString(6);
            String t = rs.getString(7);
            parameters = new HashMap<>();
            parameters.put(s,t);
            return new ProductWithParameters(p,parameters);
        }catch (Exception ex) {
            ex.printStackTrace();
        }
        return null;
    }

    @Override
    public String toString() {
        return "ProductWithParameters{" +
                "product=" + product.toString() +
                ", parametes=" + parametes +
                '}';
    }

    public static List<ProductWithParameters> accumulate(List<ProductWithParameters> list){
        int n = list.size();
        ArrayList<Boolean> consumed = new ArrayList<>();
        ArrayList<ProductWithParameters> result = new ArrayList<>();
        for(int i = 0; i < n; i++){
            consumed.add(false);
        }
        for(int i = 0; i < n; i++){
            if(!consumed.get(i)){
                for(int j = i + 1; j < n; j++){
                    if(list.get(i).product.getId() == list.get(j).product.getId()){
                        for(var key : list.get(j).parametes.keySet()){
                            list.get(i).parametes.put(key,list.get(j).parametes.get(key));
                            consumed.set(j,true);
                        }
                    }
                }
                result.add(list.get(i));
            }
        }
        return result;
    }

    public ProductWithParameters(Product product, Map<String, String> parametes) {
        this.product = product;
        this.parametes = parametes;
    }
}
