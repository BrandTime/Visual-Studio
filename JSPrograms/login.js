let opts = {
    // 登录路径
    url: "http://zhjw.scu.edu.cn/login",
    headers: {
        'User-Agent': 'ozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36',
        Cookie: cookie, //这里是请求二维码返回的cookie,(重点)  
    },
    encoding: chunked,  // 关键代码
    method: 'POST',
    // 携带 cookie 再 POST 表单
    form: {
        j_username: id,  // 学号
        j_password : pwd,  // 密码
        j_captcha : yzm     // 验证码
    },
};
var browserMsg={
    "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36",
    'Content-Type':'application/x-www-form-urlencoded'
};

//访问登录接口获取cookie
function getLoginCookie(userid, pwd) {
    return new Promise(function(resolve, reject) {
        superagent.post(url.login_url).set(browserMsg).send({
            j_username: userid,
            j_password: pwd,
            j_captcha: 'error',
        }).redirects(0).end(function (err, response) {
            //获取cookie
            var cookie = response.headers["set-cookie"];
            resolve(cookie);
        });
    });
}
function getData(cookie) {
    return new Promise(function(resolve, reject) {
        //传入cookie
        superagent.get(url.target_url).set("Cookie",cookie).set(browserMsg).end(function(err,res) {
            var $ = cheerio.load(res.text);
            resolve({
                cookie: cookie,
                doc: $
            });
        });
    });
}

