-- 插入用户数据
insert into users (user_name, pwd, college, num, email) values ('alice', 'password123', 'Engineering', 'A001', 'alice@example.com');
insert into users (user_name, pwd, college, num, email) values ('bob', 'password456', 'Science', 'B001', 'bob@example.com');
insert into users (user_name, pwd, college, num, email) values ('charlie', 'password789', 'Arts', 'C001', 'charlie@example.com');

-- 插入图书数据
insert into books (book_id, book_name, author, publish_com, publish_date) values ('B001', 'Python Basics', 'John Doe', 'ABC Press', '2023-01-01');
insert into books (book_id, book_name, author, publish_com, publish_date) values ('B002', 'Data Science 101', 'Jane Smith', 'XYZ Press', '2022-05-15');
insert into books (book_id, book_name, author, publish_com, publish_date) values ('9787208061644', '追风筝的人', '胡赛尼', '上海人民出版社', '2006-05-01');
insert into books (book_id, book_name, author, publish_com, publish_date) values ('9787549529322', '看见', '柴静', '广西师范大学出版社', '2013-01-01');
insert into books (book_id, book_name, author, publish_com, publish_date) values ('9787507423846', '梦的解析', '弗洛伊德', '中国城市出版社', '2011-01-01');
insert into books (book_id, book_name, author, publish_com, publish_date) values ('9787530201244', '穆斯林的葬礼', '霍达', '北京十月文艺出版社', '1988-12-01');
insert into books (book_id, book_name, author, publish_com, publish_date) values ('9787020068425', '再见，哥伦布', '菲利普·罗斯', '人民文学出版社', '2009-06-03');

-- 查询所有用户信息
select * from users;

-- 查询所有图书信息
select * from books;

-- 查询所有借阅记录
select * from borrows;

-- 查询所有历史记录
select * from histroys;


-- 根据用户名查询用户信息
select * from users where user_name = 'alice';

-- 根据图书ID查询图书信息
select * from books where book_id = 'B001';

-- 查询某个用户的借阅记录
select * from borrows where user_name = 'alice';

-- 查询某本图书的借阅记录
select * from borrows where book_id = 'B002';

-- 查询未归还的图书记录
select * from borrows where date_return is null;

-- 查询某个用户的历史借阅记录
select * from histroys where user_name = 'alice';

-- 查询某本图书的历史借阅记录
select * from histroys where book_id = 'B001';

-- 查询状态为“not return”的历史记录
select * from histroys where status = 'not return';




-- 查询某个学院的所有用户
select * from users where college = 'Engineering';

-- 查询某个日期之后出版的所有图书
select * from books where publish_date > '2020-01-01';

-- 查询按作者分组的图书数量
select author, count(*) as book_count from books group by author;

-- 查询每个用户的借阅数量
select user_name, count(*) as borrow_count from borrows group by user_name;





