package main;

import entity.Parameter;
import entity.ParameterGroup;
import entity.Product;
import entity.ProductGroup;
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

    public List<Parameter> selectParameterList(){
        ArrayList<Parameter> result = new ArrayList<>();
        try{
            CachedRowSet rs = selectQuery("select * from parameter");
            while (rs.next()) {
                result.add(Parameter.parseParameter(rs));
            }
        } catch (SQLException e) {
            throw new Error("Couldn't parse route: ", e);
        }
        return result;
    }

    public void insertParameter(Parameter parameter){
        String query = "insert into Parameter (name, unit, groupId) "
                + "VALUES (" + parameter.toStringInsert() + ")";
        updateQuery(query);
    }

    public void updateParameter(int id, Parameter parameter){
        String query = "UPDATE Parameter set ";
        query += parameter.toStringUpdate();
        query += " WHERE id = " +  id;
        updateQuery(query);
    }

    public void deleteParameter(int id){
        String query = "DELETE FROM Parameter WHERE id = " + id;
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

    public List<Product> selectProductList(){
        ArrayList<Product> result = new ArrayList<>();
        try{
            CachedRowSet rs = selectQuery("select * from Product");
            while (rs.next()) {
                result.add(Product.parseProduct(rs));
            }
        } catch (SQLException e) {
            throw new Error("Couldn't parse route: ", e);
        }
        return result;
    }

    public void insertProduct(Product Product){
        String query = "insert into Product (name, unit, groupId) "
                + "VALUES (" + Product.toStringInsert() + ")";
        updateQuery(query);
    }

    public void updateProduct(int id, Product Product){
        String query = "UPDATE Product set ";
        query += Product.toStringUpdate();
        query += " WHERE id = " +  id;
        updateQuery(query);
    }

    public void deleteProduct(int id){
        String query = "DELETE FROM Product WHERE id = " + id;
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
                + "VALUES (" + ParameterGroup.toStringInsert() + ")";
        updateQuery(query);
    }

    public void updateParameterGroup(int id, ParameterGroup ParameterGroup){
        String query = "UPDATE ParameterGroup set ";
        query += ParameterGroup.toStringUpdate();
        query += " WHERE id = " +  id;
        updateQuery(query);
    }

    public void deleteParameterGroup(int id){
        String query = "DELETE FROM ParameterGroup WHERE id = " + id;
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
                + "VALUES (" + ProductGroup.toStringInsert() + ")";
        updateQuery(query);
    }

    public void updateProductGroup(int id, ProductGroup ProductGroup){
        String query = "UPDATE ProductGroup set ";
        query += ProductGroup.toStringUpdate();
        query += " WHERE id = " +  id;
        updateQuery(query);
    }

    public void deleteProductGroup(int id){
        String query = "DELETE FROM ProductGroup WHERE id = " + id;
        updateQuery(query);
    }

}
