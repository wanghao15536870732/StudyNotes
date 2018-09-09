# 第十五章：DAO设计模式

## 15.3  项目准备

### 范例15-1：定义数据库的连接类

```java
package com.yootk.dbc;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
/**
 * 本类专门负责数据库的连接与关闭操作，在实例化本类对象时就意味着要进行数据库的开发<br>
 * 所以在本类的构造方法里要进行数据库驱动加载与数据库连接取得
 */
public class DatabaseConnection { 
    private static final String DBDRIVER = "oracle.jdbc.driver.OracleDriver" ;
    private static final String DBURL = "jdbc:oracle:thin:@localhost:1521:yootk" ;
    private static final String DBUSER = "scott" ;
    private static final String PASSWORD = "tiger" ;
    private Connection conn = null ;
    /**
     * 在构造方法里面为conn对象进行实例化，可以直接取得数据库的连接对象<br>
     * 由于所有的操作都是基于数据库完成的，如果数据库无法取得连接，也就意味着所有的操作都可以停止了
     */
    public DatabaseConnection() {
        try {
            Class.forName(DBDRIVER) ;
            this.conn = DriverManager.getConnection(DBURL,DBUSER,PASSWORD) ;
        } catch (Exception e) {	// 虽然此处有异常，但是抛出的意义不大
            e.printStackTrace();
        }
    }
    /**
     * 取得一个数据库的连接对象
     * @return Connection实例化对象
     */
    public Connection getConnection() {
        return this.conn ;
    }
    /**
     * 负责数据库的关闭
     */
    public void close() {
        if (this.conn != null) {		// 表示存在连接对象
           try {
               this.conn.close();	// 关闭数据库连接
           } catch (SQLException e) {
               e.printStackTrace();
           }
        }
    }
}

```

## 15.4  开发数据层

### 范例15-3：定义IEmpDAO接口

```java
package com.yootk.dao;
import java.util.List;
import java.util.Set;
import com.yootk.vo.Emp;
/**
 * 定义emp表的数据层的操作标准
 */
public interface IEmpDAO {
    /**
     * 实现数据的增加操作
     * @param vo 包含了要增加数据的VO对象
     * @return 数据保存成功返回true，否则返回false
     * @throws Exception SQL执行异常
     */
    public boolean doCreate(Emp vo) throws Exception ;
    /**
     * 实现数据的修改操作，本次修改是根据id进行全部字段数据的修改
     * @param vo 包含了要修改数据的信息，一定要提供ID内容
     * @return 数据修改成功返回true，否则返回false
     * @throws Exception SQL执行异常
     */
    public boolean doUpdate(Emp vo) throws Exception ;
    /**
     * 执行数据的批量删除操作，所有要删除的数据以Set集合的形式保存
     * @param ids 包含了所有要删除的数据ID，不包含重复内容
     * @return 删除成功返回true（删除的数据个数与要删除的数据个数相同），否则返回false。
     * @throws Exception SQL执行异常
     */
    public boolean doRemoveBatch(Set<Integer> ids) throws Exception ;
    /**
     * 根据雇员编号查询指定的雇员信息
     * @param id 要查询的雇员编号
     * @return 如果雇员信息存在，则将数据以VO类对象的形式返回，如果雇员数据不存在，则返回null
     * @throws Exception SQL执行异常
     */
    public Emp findById(Integer id) throws Exception ;
    /**
     * 查询指定数据表的全部记录，并且以集合的形式返回
     * @return 如果表中有数据，则所有的数据会封装为VO对象后利用List集合返回，<br>
     * 如果没有数据，那么集合的长度为0（size() == 0，不是null）
     * @throws Exception SQL执行异常
     */
    public List<Emp> findAll() throws Exception ;
    /**
     * 分页进行数据的模糊查询，查询结果以集合的形式返回
     * @param currentPage 当前所在的页
     * @param lineSize 每行显示数据行数
     * @param column 要进行模糊查询的数据列
     * @param keyWord 模糊查询的关键字
     * @return 如果表中有数据，则所有的数据会封装为VO对象后利用List集合返回，<br>
     * 如果没有数据，那么集合的长度为0（size() == 0，不是null）
     * @throws Exception SQL执行异常
     */
    public List<Emp> findAllSplit(Integer currentPage, Integer lineSize, String column, String keyWord) throws Exception;
    /**
     * 进行模糊查询数据量的统计，如果表中没有记录，统计的结果就是0
     * @param column 要进行模糊查询的数据列
     * @param keyWord 模糊查询的关键字
     * @return 返回表中的数据量，如果没有数据返回0
     * @throws Exception SQL执行异常
     */
    public Integer getAllCount(String column,String keyWord) throws Exception ;
}

```

## 范例15-4：EmpDAOImpl子类

```javapackage com.yootk.dao.impl;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import com.yootk.dao.IEmpDAO;
import com.yootk.vo.Emp;
/**
 * 定义emp表的数据层的具体实现子类
 * @author 极限IT（www.jixianit.com）
 */
public class EmpDAOImpl implements IEmpDAO {// 实现IEmpDAO接口
    private Connection conn ;// 需要利用Connection对象操作
    private PreparedStatement pstmt ;// 定义数据库操作对象
    /*
     * 如果要使用数据层进行原子性的功能操作实现，必须要提供Connection接口对象<br>
     * 另外，由于开发中业务层要调用数据层，所以数据库的打开与关闭交由业务层处理
     * @param conn 表示数据库连接对象
     */
    public EmpDAOImpl(Connection conn) {// 传递Connection接口对象
        this.conn = conn ;// 保存数据库连接
    }
    @Override
    public boolean doCreate(Emp vo) throws Exception {
        String sql = "INSERT INTO emp(empno,ename,job,hiredate,sal,comm) VALUES (?,?,?,?,?,?)" ;
        this.pstmt = this.conn.prepareStatement(sql) ;// 创建数据库操作对象
        this.pstmt.setInt(1, vo.getEmpno());// 设置字段内容
        this.pstmt.setString(2, vo.getEname());// 设置字段内容	
        this.pstmt.setString(3, vo.getJob());// 设置字段内容
        // 将java.util.Date类的对象转换为java.sql.Date类对象
        this.pstmt.setDate(4, new java.sql.Date(vo.getHiredate().getTime()));
        this.pstmt.setDouble(5, vo.getSal());// 设置字段内容
        this.pstmt.setDouble(6, vo.getComm());// 设置字段内容
        return this.pstmt.executeUpdate() > 0 ;// 执行数据更新操作
    }
    @Override
    public boolean doUpdate(Emp vo) throws Exception {
        String sql = "UPDATE emp SET ename=?,job=?,hiredate=?,sal=?,comm=? WHERE empno=?" ;
        this.pstmt = this.conn.prepareStatement(sql) ;// 创建数据库操作对象
        this.pstmt.setString(1, vo.getEname());// 设置字段内容
        this.pstmt.setString(2, vo.getJob());// 设置字段内容
        // 将java.util.Date类的对象转换为java.sql.Date类对象
        this.pstmt.setDate(3, new java.sql.Date(vo.getHiredate().getTime()));
        this.pstmt.setDouble(4, vo.getSal());// 设置字段内容
        this.pstmt.setDouble(5, vo.getComm());// 设置字段内容
        this.pstmt.setInt(6, vo.getEmpno());// 设置字段内容
        return this.pstmt.executeUpdate() > 0 ;// 执行数据更新操作
    }
    @Override
    public boolean doRemoveBatch(Set<Integer> ids) throws Exception {
        StringBuffer sql = new StringBuffer() ;// 拼凑SQL
        sql.append("DELETE FROM emp WHERE empno IN(") ;// 追加SQL语句
        Iterator<Integer> iter = ids.iterator() ;// 迭代每一个删除ID
        while (iter.hasNext()) {
            sql.append(iter.next()).append(",") ;// 追加SQL
        }
        sql.delete(sql.length()-1, sql.length()).append(")") ;// 处理SQL
        this.pstmt = this.conn.prepareStatement(sql.toString()) ;// 创建数据库操作对象
        return this.pstmt.executeUpdate() == ids.size();// 执行数据更新操作
    }
    @Override
    public Emp findById(Integer id) throws Exception {
        Emp vo = null ;// 定义VO对象
        String sql = "SELECT empno,ename,job,hiredate,sal,comm FROM emp WHERE empno=?" ;
        this.pstmt = this.conn.prepareStatement(sql) ;// 创建数据库操作对象
        this.pstmt.setInt(1, id);// 设置字段内容
        ResultSet rs = this.pstmt.executeQuery() ;			// 执行数据查询操作
        if (rs.next()) {// 已经找到数据
           vo = new Emp() ;// 实例化VO对象
           vo.setEmpno(rs.getInt(1));// 读取列内容并将数据保存在属性中
           vo.setEname(rs.getString(2));					// 读取列内容并将数据保存在属性中
           vo.setJob(rs.getString(3));// 读取列内容并将数据保存在属性中
           vo.setHiredate(rs.getDate(4));					// 读取列内容并将数据保存在属性中
           vo.setSal(rs.getDouble(5));						// 读取列内容并将数据保存在属性中
           vo.setComm(rs.getDouble(6));					// 读取列内容并将数据保存在属性中
        }
        return vo ;									// 返回VO类对象
    }
    @Override
    public List<Emp> findAll() throws Exception {
        List<Emp> all = new ArrayList<Emp>() ;			// 实例化集合对象
        String sql = "SELECT empno,ename,job,hiredate,sal,comm FROM emp" ;
        this.pstmt = this.conn.prepareStatement(sql) ; 		// 创建数据库操作对象
        ResultSet rs = this.pstmt.executeQuery() ;			// 执行数据查询操作
        while (rs.next()) {								// 有多条数据返回，循环多次
            Emp vo = new Emp() ;						// 实例化VO对象
            vo.setEmpno(rs.getInt(1));					// 读取列内容并将数据保存在属性中
            vo.setEname(rs.getString(2));					// 读取列内容并将数据保存在属性中
            vo.setJob(rs.getString(3));					// 读取列内容并将数据保存在属性中
            vo.setHiredate(rs.getDate(4));					// 读取列内容并将数据保存在属性中
            vo.setSal(rs.getDouble(5));					// 读取列内容并将数据保存在属性中
            vo.setComm(rs.getDouble(6));					// 读取列内容并将数据保存在属性中
            all.add(vo) ;								// 向集合保存数据
        }
        return all;									// 返回集合
    }
    @Override
    public List<Emp> findAllSplit(Integer currentPage, Integer lineSize, String column, String keyWord) throws Exception {
        List<Emp> all = new ArrayList<Emp>() ;			// 定义集合
        String sql = "SELECT * FROM " + 
                   " (SELECT empno,ename,job,hiredate,sal,comm,ROWNUM rn" + 
                   " FROM emp" + " WHERE " + column + " LIKE ? AND ROWNUM<=?) temp " + 
                   " WHERE temp.rn>? "; 				// 执行SQL分页语句
        this.pstmt = this.conn.prepareStatement(sql) ;	// 创建数据库操作对象
        this.pstmt.setString(1, "%" + keyWord + "%");		// 设置字段内容
        this.pstmt.setInt(2, currentPage * lineSize);	// 设置字段内容
        this.pstmt.setInt(3, (currentPage - 1) * lineSize); 		// 设置字段内容
        ResultSet rs = this.pstmt.executeQuery() ;			// 执行数据查询操作
        while (rs.next()) {								// 循环取出每一行数据
            Emp vo = new Emp() ;						// 实例化VO对象
            vo.setEmpno(rs.getInt(1));					// 读取列内容并将数据保存在属性中
            vo.setEname(rs.getString(2));					// 读取列内容并将数据保存在属性中
            vo.setJob(rs.getString(3));					// 读取列内容并将数据保存在属性中
            vo.setHiredate(rs.getDate(4));					// 读取列内容并将数据保存在属性中
            vo.setSal(rs.getDouble(5));					// 读取列内容并将数据保存在属性中
            vo.setComm(rs.getDouble(6));					// 读取列内容并将数据保存在属性中
            all.add(vo) ;								// 向集合保存数据
        }
        return all;									// 返回List集合数据
    }
    @Override
    public Integer getAllCount(String column, String keyWord) throws Exception {
        String sql = "SELECT COUNT(empno) FROM emp WHERE " + column + " LIKE ?" ;
        this.pstmt = this.conn.prepareStatement(sql) ; 		// 创建数据库操作对象
        this.pstmt.setString(1, "%" + keyWord + "%");		// 设置字段内容
        ResultSet rs = this.pstmt.executeQuery() ;			// 执行数据查询操作
        if (rs.next()) {								// COUNT()统计一定会返回结果
           return rs.getInt(1) ;							// 返回读取的第一列数据
        }
        return 0;									// 如果没有数据返回0 
    }
}

```

## 范例15-5：定义工厂类

```java
package com.yootk.factory;
import java.sql.Connection;
import com.yootk.dao.IEmpDAO;
import com.yootk.dao.impl.EmpDAOImpl;
/**
 * 定义DAO工厂类，以后的DAO接口对象将通过此工厂类取得
 */
public class DAOFactory {
    /**
     * 取得IEmpDAO接口对象，通过EmpDAOImpl子类实例化
     * @param conn EmpDAOImpl构造方法需要接收数据库连接对象
     * @return IEmpDAO接口实例化对象
     */
    public static IEmpDAO getIEmpDAOInstance(Connection conn) {
        return new EmpDAOImpl(conn) ;			// 实例化EmpDAOImpl子类对象
    }
}

```

## 15.5  开发业务层

### 范例15-6：定义IEmpService操作标准。

```java
package com.yootk.service;
import java.util.List;
import java.util.Map;
import java.util.Set;
import com.yootk.vo.Emp;
/**
 * 定义emp表的业务层的执行标准，此类一定要负责数据库的打开与关闭操作
 * 此类可以通过DAOFactory类取得IEmpDAO接口对象
 */
public interface IEmpService {
    /**
     * 实现雇员数据的增加操作，本次操作要调用IEmpDAO接口的方法：<br>
     * <li>需要调用IEmpDAO.findById()方法，判断要增加数据的id是否已经存在；</li>
     * <li>如果要增加的数据编号不存在，则调用IEmpDAO.doCreate()方法，返回操作的结果。</li>
     * @param vo 包含了要增加数据的VO对象
     * @return 如果增加数据的ID重复或保存失败，则返回false，否则返回true
     * @throws Exception SQL执行异常
     */
    public boolean insert(Emp vo) throws Exception ;
    /**
     * 实现雇员数据的修改操作，本次要调用IEmpDAO.doUpdate()方法，本次修改属于全部内容的修改
     * @param vo 包含了要修改数据的VO对象
     * @return 修改成功返回true，否则返回false
     * @throws Exception SQL执行异常
     */
    public boolean update(Emp vo) throws Exception ;
    /**
     * 执行雇员数据的删除操作，可以删除多个雇员信息，调用IEmpDAO.doRemoveBatch()方法
     * @param ids 包含了全部要删除数据的集合，没有重复数据
     * @return 删除成功返回true，否则返回false
     * @throws Exception SQL执行异常
     */
    public boolean delete(Set<Integer> ids) throws Exception ;
    /**
     * 根据雇员编号查找雇员的完整信息，调用IEmpDAO.findById()方法
     * @param ids 要查找的雇员编号
     * @return 如果找到了，则将雇员信息以VO对象返回，否则返回null
     * @throws Exception SQL执行异常
     */
    public Emp get(int ids) throws Exception ;
    /**
     * 查询全部雇员信息，调用IEmpDAO.findAll()方法
     * @return 查询结果以List集合的形式返回，如果没有数据则集合的长度为0
     * @throws Exception SQL执行异常
     */
    public List<Emp> list() throws Exception ;
    /**
     * 实现数据的模糊查询与数据统计，要调用IEmpDAO接口的两个方法：<br>
     * <li>调用IEmpDAO.findAllSplit()方法，查询所有的表数据，返回的是List<Emp>；</li>
     * <li>调用IEmpDAO.getAllCount()方法，查询所有的数据量，返回的是Integer；</li>
     * @param currentPage 当前所在页
     * @param lineSize 每页显示的记录数
     * @param column 模糊查询的数据列
     * @param keyWord 模糊查询关键字
     * @return 本方法由于需要返回多种数据类型，所以使用Map集合返回，由于类型不统一，所以所有value的类型设置为Object，返回内容如下。<br>
     * <li>key = allEmps，value = IEmpDAO.findAllSplit()返回结果（List<Emp>类型）</li>
     * <li>key = empCount，value = IEmpDAO.getAllCount()返回结果（Integer类型）</li>
     * @throws Exception SQL执行异常
     */
    public Map<String, Object> list(int currentPage, int lineSize, String column, String keyWord) throws Exception;
}

```

### 范例15-7：定义EmpServiceImpl子类

```java
package com.yootk.service.impl;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import com.yootk.dbc.DatabaseConnection;
import com.yootk.factory.DAOFactory;
import com.yootk.service.IEmpService;
import com.yootk.vo.Emp;
public class EmpServiceImpl implements IEmpService {
    // 在这个类的对象内部提供了一个数据库连接类的实例化对象
    private DatabaseConnection dbc = new DatabaseConnection();
    @Override
    public boolean insert(Emp vo) throws Exception {
        try {
            // 要增加的雇员编号如果不存在，则findById()返回的结果就是null
            // null表示可以保存新增雇员数据
            if (DAOFactory.getIEmpDAOInstance(this.dbc.getConnection())
                     .findById(vo.getEmpno()) == null) {
            // 直接返回IEmpDAO.doCreate()方法的处理结果
               return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).doCreate(vo);
            }
            return false;					// 增加失败
        } catch (Exception e) {
            throw e;						// 有异常交给被调用处进行处理
        } finally {
            this.dbc.close();				// 不管数据层操作是否有异常，一定要关闭数据库连接
        }
    }
    @Override
    public boolean update(Emp vo) throws Exception {
        try {// 更新操作将根据id进行全部更新，此处将直接返回数据层处理结果
            return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).doUpdate(vo);
        } catch (Exception e) {
            throw e;						// 如果有异常，交给被调用处进行处理
        } finally {
            this.dbc.close();				// 不管数据层操作是否有异常，一定要关闭数据库连接
        }
    }
    @Override
    public boolean delete(Set<Integer> ids) throws Exception {
        try {
            if (ids == null || ids.size() == 0) {	// 没有要删除的数据
               return false ;				// 直接返回false
            }
            // 如果此时集合内容不为空，则调用数据层实现数据删除处理
            return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).doRemoveBatch(ids);
        } catch (Exception e) {
            throw e;						// 如果有异常，交给被调用处进行处理
        } finally {
            this.dbc.close();				// 不管数据层操作是否有异常，一定要关闭数据库连接
        }
    }
    @Override
    public Emp get(int ids) throws Exception {
        try {
            // 直接调用数据层返回指定id的数据
            return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).findById(ids);
        } catch (Exception e) {
            throw e;						// 如果有异常，交给被调用处进行处理
        } finally {
            this.dbc.close();				// 不管数据层操作是否有异常，一定要关闭数据库连接
        }
    }
    @Override
    public List<Emp> list() throws Exception {
        try {
            // 直接调用数据层返回emp表的全部记录
            return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).findAll();
        } catch (Exception e) {
            throw e;						// 如果有异常，交给被调用处进行处理
        } finally {
            this.dbc.close();				// 不管数据层操作是否有异常，一定要关闭数据库连接
        }
    }
    @Override
    public Map<String, Object> list(int currentPage, int lineSize, String column, 
        String keyWord)  throws Exception {
        try {
            // 由于此方法需要返回多种类型的数据，所以使用Map集合保存返回数据
            Map<String, Object> map = new HashMap<String, Object>();
            // 分页查询出emp表中的部分数据内容
            map.put("allEmps", DAOFactory.getIEmpDAOInstance(this.dbc.getConnection())
                 .findAllSplit(currentPage, lineSize, column, keyWord));
            // 统计出emp表中的数据量
            map.put("empCount", DAOFactory.getIEmpDAOInstance(this.dbc.getConnection())
                 .getAllCount(column, keyWord));
            return map; 
        } catch (Exception e) {
            throw e;						// 如果有异常，交给被调用处进行处理
        } finally {
            this.dbc.close();				// 不管数据层操作是否有异常，一定要关闭数据库连接
        }
    }
}

```

### 范例15-8：定义ServiceFactory

```java
package com.yootk.factory;
import com.yootk.service.IEmpService;
import com.yootk.service.impl.EmpServiceImpl;
public class ServiceFactory {
    /**
     * 取得IEmpService接口对象
     * @return IEmpService接口的实例化对象
     */
    public static IEmpService getIEmpServiceInstance() {
        return new EmpServiceImpl();
    }
}

```