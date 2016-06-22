var os = require('os');


function add(var1, var2) {
    var ret = var1 + var2;
    console.log("add ret:%d", ret );
}


add(10, 20);


var student = {
    name: 'Jack',
    sex: 'M', 
    age:  20,
    print: function() {
        console.log("name:%s sex:%s age:%s", this.name, this.sex, this.age);
    }
};


student.print();


console.log(os.release());
