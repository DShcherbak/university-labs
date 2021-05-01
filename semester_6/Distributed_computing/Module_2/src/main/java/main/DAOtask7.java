package main;

import entity.*;
import jdbc.ConnectionPool;

import javax.sql.rowset.CachedRowSet;
import javax.sql.rowset.RowSetFactory;
import javax.sql.rowset.RowSetProvider;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class DAOtask7 {

    private CachedRowSet selectQuery(String query){
        try{
            RowSetFactory rowSetFactory = RowSetProvider.newFactory();
            CachedRowSet cachedRowSet = rowSetFactory.createCachedRowSet();
            try{
                Connection conn = ConnectionPool.getConnectionPool().getConnection();
                try (Statement stmt = conn.createStatement()) {
                    ResultSet rs = stmt.executeQuery(query);
                    cachedRowSet.populate(rs);
                } catch (SQLException e) {
                    e.printStackTrace();
                }
                ConnectionPool.getConnectionPool().releaseConnection(conn);
            }
            catch (Exception ex){
                ex.printStackTrace();
            }
            return cachedRowSet;
        }catch (SQLException throwable) {
            System.out.println("Couldn't create rowSetFactory.");
            throwable.printStackTrace();
        }
        return null;
    }

    private void updateQuery(String query) {
        try{
            Connection conn = ConnectionPool.getConnectionPool().getConnection();
            try (Statement stmt = conn.createStatement()) {
                stmt.executeUpdate(query);
            } catch (SQLException e) {
                e.printStackTrace();
            }
            ConnectionPool.getConnectionPool().releaseConnection(conn);
        }catch (Exception ex){
            ex.printStackTrace();
        }
    }

    public Parameter selectParameter(int id){
        Parameter result = null;
        try{
            CachedRowSet rs = selectQuery("select * from Parameter where id = " + id);
            while (rs.next()) {
                result = Parameter.parseParameter(rs);
            }
        } catch (SQLException e) {
            throw new Error("Couldn't parse route: ", e);
        }
        return result;
    }

    private List<Parameter> selectParameterListInternal(String query){
        ArrayList<Parameter> result = new ArrayList<>();
        try{
            CachedRowSet rs = selectQuery(query);
            while (rs.next()) {
                result.add(Parameter.parseParameter(rs));
            }
        } catch (SQLException e) {
            throw new Error("Couldn't parse route: ", e);
        }
        return result;
    }

    public List<Parameter> selectParameterList(){
        return selectParameterListInternal("select * from parameter");
    }

    public void insertParameter(Parameter parameter){
        String query = "insert into Parameter (name, unit, groupId) "
                + "values (" + parameter.toStringInsert() + ")";
        updateQuery(query);
    }

    public void updateParameter(int id, Parameter parameter){
        String query = "update Parameter set ";
        query += parameter.toStringUpdate();
        query += " where id = " +  id;
        updateQuery(query);
    }

    public void deleteParameter(int id){
        String query = "delete from Parameter where id = " + id;
        updateQuery(query);
    }

    public Product selectProduct(int id){
        Product result = null;
        try{
            CachedRowSet rs = selectQuery("select * from Product where id = " + id);
            while (rs.next()) {
                result = Product.parseProduct(rs);
            }
        } catch (SQLException e) {
            throw new Error("Couldn't parse route: ", e);
        }
        return result;
    }

    private List<Product> selectProductListInternal(String query){
        ArrayList<Product> result = new ArrayList<>();
        try{
            CachedRowSet rs = selectQuery(query);
            while (rs.next()) {
                result.add(Product.parseProduct(rs));
            }
        } catch (SQLException e) {
            throw new Error("Couldn't parse route: ", e);
        }
        return result;
    }

    public List<Product> selectProductList(){
        return selectProductListInternal("select * from Product");
    }

    public void insertProduct(Product Product){
        String query = "insert into Product (name, unit, groupId) "
                + "values (" + Product.toStringInsert() + ")";
        updateQuery(query);
    }

    public void updateProduct(int id, Product Product){
        String query = "update Product set ";
        query += Product.toStringUpdate();
        query += " where id = " +  id;
        updateQuery(query);
    }

    public void deleteProduct(int id){
        String query = "delete from Product where id = " + id;
        updateQuery(query);
    }

    public ParameterGroup selectParameterGroup(int id){
        ParameterGroup result = null;
        try{
            CachedRowSet rs = selectQuery("select * from ParameterGroup where id = " + id);
            while (rs.next()) {
                result = ParameterGroup.parseParameterGroup(rs);
            }
        } catch (SQLException e) {
            throw new Error("Couldn't parse route: ", e);
        }
        return result;
    }

    public List<ParameterGroup> selectParameterGroupList(){
        ArrayList<ParameterGroup> result = new ArrayList<>();
        try{
            CachedRowSet rs = selectQuery("select * from ParameterGroup");
            while (rs.next()) {
                result.add(ParameterGroup.parseParameterGroup(rs));
            }
        } catch (SQLException e) {
            throw new Error("Couldn't parse route: ", e);
        }
        return result;
    }

    public void insertParameterGroup(ParameterGroup ParameterGroup){
        String query = "insert into ParameterGroup (name, unit, groupId) "
                + "values (" + ParameterGroup.toStringInsert() + ")";
        updateQuery(query);
    }

    public void updateParameterGroup(int id, ParameterGroup ParameterGroup){
        String query = "update ParameterGroup set ";
        query += ParameterGroup.toStringUpdate();
        query += " where id = " +  id;
        updateQuery(query);
    }

    public void deleteParameterGroup(int id){
        String query = "delete from ParameterGroup where id = " + id;
        updateQuery(query);
    }

    public ProductGroup selectProductGroup(int id){
        ProductGroup result = null;
        try{
            CachedRowSet rs = selectQuery("select * from ProductGroup where id = " + id);
            while (rs.next()) {
                result = ProductGroup.parseProductGroup(rs);
            }
        } catch (SQLException e) {
            throw new Error("Couldn't parse route: ", e);
        }
        return result;
    }

    public List<ProductGroup> selectProductGroupList(){
        ArrayList<ProductGroup> result = new ArrayList<>();
        try{
            CachedRowSet rs = selectQuery("select * from ProductGroup");
            while (rs.next()) {
                result.add(ProductGroup.parseProductGroup(rs));
            }
        } catch (SQLException e) {
            throw new Error("Couldn't parse route: ", e);
        }
        return result;
    }

    public void insertProductGroup(ProductGroup ProductGroup){
        String query = "insert into ProductGroup (name, unit, groupId) "
                + "values (" + ProductGroup.toStringInsert() + ")";
        updateQuery(query);
    }

    public void updateProductGroup(int id, ProductGroup ProductGroup){
        String query = "update ProductGroup set ";
        query += ProductGroup.toStringUpdate();
        query += " where id = " +  id;
        updateQuery(query);
    }

    public void deleteProductGroup(int id){
        String query = "delete from ProductGroup where id = " + id;
        updateQuery(query);
    }


    //Вывести перечень параметров для заданной группы продукции.
    public List<Parameter> task1(int groupId){
        String query = "select distinct pa.* from parameter pa " +
                "inner join parameterGroup pag on  pa.groupId = pag.Id " +
                "inner join group_x_group gg on gg.parameterId = pag.Id " +
                "inner join productGroup prg on prg.id = gg.productId " +
                "where prg.id = " + groupId;
        return selectParameterListInternal(query);
    }

    //Вывести перечень продукции, не содержащий заданного параметра.
    public List<Product> task2(int parameterId){
        String query = "select * from product where not id in " +
                    "(select productId from product_x_parameter where parameterId = " + parameterId + ")";
        return selectProductListInternal(query);
    }

    //Вывести информацию о продукции для заданной группы
    public List<Product> task3(int groupId){
        String query = "select * from product where product.groupId = " + groupId;
        return selectProductListInternal(query);
    }

    //Вывести информацию о продукции для заданной группы
    public List<ProductWithParameters> task4(int groupId){
        String query = "select * from product where product.groupId = " + groupId;
        List<ProductWithParameters> result = new ArrayList<>();
        try{
            CachedRowSet rs = selectQuery(query);
            while (rs.next()) {
                result.add(ProductWithParameters.parseProduct(rs));
            }
        } catch (SQLException e) {
            throw new Error("Couldn't parse route: ", e);
        }
        result = ProductWithParameters.accumulate(result);
        return result;
    }

    private String makeStringList(List<Integer> list){
        StringBuilder result = new StringBuilder("(");
        for(var elem : list){
            result.append(elem.toString()).append(",");
        }
        return result.substring(0, result.length()-1) + ")";
    }

    //Удалить из базы продукцию, содержащую заданные параметры.
    public void task5(List<Integer> parameters) {
        String list = makeStringList(parameters);
        String sql = "delete from Product where id in " +
                "(select productId from product_x_parameter where parameterId in " + list + ")";
        updateQuery(sql);
        sql = "delete from product_x_parameter where parameterId in " + list;
        updateQuery(sql);
    }

    //Переместить группу параметров из одной группы товаров в другую.
    public void task6(long parameterGroupId, long fromGroupId, long toGroupId) {
        String sql = "update group_x_group set productId = " + toGroupId + " where productId = " + fromGroupId + " and parameterId = " + parameterGroupId;
        updateQuery(sql);
    }


}
