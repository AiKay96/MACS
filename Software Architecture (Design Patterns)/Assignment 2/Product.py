class Product:
    def __init__(self, product_id,
                 name,
                 quantity,
                 has_discount,
                 discount_percent,
                 price,
                 in_batches,
                 batch_amount,
                 batch_size,
                 batch_discount):
        self.id = product_id
        self.name = name
        self.quantity = quantity
        self.has_discount = has_discount
        self.discount_percent = discount_percent
        self.price = price
        self.in_batches = in_batches
        self.batch_amount = batch_amount
        self.batch_size = batch_size
        self.batch_discount = batch_discount

    def open_batch(self, amount):
        if not self.in_batches:
            return 0
        without_batch = self.quantity - self.batch_size * self.batch_amount
        if amount < without_batch:
            return 0
        from_batch = amount - without_batch
        batches_needed = (from_batch + self.batch_size - 1) // self.batch_size

        return batches_needed


class Report:
    def __init__(self, product_name, amount, payment_type, revenue):
        self.product_name = product_name
        self.amount = amount
        self.payment_type = payment_type
        self.revenue = revenue

    def print_report(self):
        print(self.product_name, '|',  self.amount)
