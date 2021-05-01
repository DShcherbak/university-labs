package entity;

import javax.sql.RowSet;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ProductWithParameters {
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
            parameters.put(rs.getString(6), rs.getString(7));
        }catch (Exception ex) {
            ex.printStackTrace();
        }
        return null;
    }

    public static List<ProductWithParameters> accumulate(List<ProductWithParameters> list){
        int n = list.size();
        ArrayList<Boolean> consumed = new ArrayList<>(n);
        ArrayList<ProductWithParameters> result = new ArrayList<>();
        for(int i = 0; i < n; i++){
            consumed.set(i,false);
        }
        for(int i = 0; i < n; i++){
            if(!consumed.get(i)){
                for(int j = i + 1; j < n; j++){
                    if(list.get(i).product.getId() == list.get(j).product.getId()){
                        for(var key : list.get(j).parametes.keySet()){
                            list.get(i).parametes.put(key,list.get(j).parametes.get(key));
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
